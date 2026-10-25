#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#define MAXBUFF 1024 * 1024
char buff[MAXBUFF];
char* buffp = buff;

void* alloc(size_t size);
void afree(void* buff);

#define F_NUMERIC 0x01      // 0000 0001
#define F_REVERSE 0x02      // 0000 0010
#define F_CASE_FOLDING 0x04 // 0000 0100

#define MAXLINES 5000       /* max #lines to be sorted */
char* lineptr[MAXLINES];    /* pointers to text lines */

int GetLine(char buff[], int maxline);
int readlines(char* lineptr[], int maxline);
void writelines(char* lineptr[], int nlines);

void Qsort(void* v[], int left, int right,
            int (*comp)(void*, void*), unsigned char flags);
int numcmp(const char*, const char*);
int Strcmp(const char*, const char*);

#define IS_UPPER(x) ((x) >= 'A' && (x) <= 'Z') ? 1 : 0
#define TO_LOWER(x) (IS_UPPER(x)) ? ((x) - 'A') + 'a' : x

/* sort input lines */
int main(int argc, char* argv[])
{
    int nlines;                 /* number if input lines read */
    unsigned char flags = 0;    /* flags for argument */

    while(--argc > 0 && **++argv == '-')
    {
        while(*++*argv != '\0')
        {
            switch (**argv)
            {
                case 'n':
                    flags |= F_NUMERIC;
                    break;
                case 'r':
                    flags |= F_REVERSE;
                    break;
                case 'f':
                    flags |= F_CASE_FOLDING;
                    break;
                default:
                    puts("error: argument");
                    break;
            }
        }
    }

    if((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        Qsort((void**) lineptr, 0, nlines-1,
            (int (*)(void*, void*))((flags & F_NUMERIC) ? numcmp :
                (flags & F_CASE_FOLDING) ? Strcmp : strcmp), flags);
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        puts("input too big to sort");
        return 1;
    }
}

void* alloc(size_t size)
{
    return ((buffp += size) <= (buff+MAXBUFF)) ? (buffp-size) : NULL;
}

void afree(void* pbuff)
{
    buffp = (char*)pbuff;
}

int GetLine(char buff[], int maxline)
{
    char* pbuff = buff;
    int c;
    while(maxline-- > 0 && (c = getchar()) != EOF && c != '\n')
        *pbuff++ = c;

    return (pbuff - buff);
}

int readlines(char* lineptr[], int maxline)
{
    int len, nlines = 0;
    char* p, line[MAXLINES];

    while((len = GetLine(line, 10)) > 0)
    {
        if(nlines >= maxline || (p = (char*)alloc(len+1)) == NULL)
            return -1;
        else
        {
            line[len] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

void writelines(char* lineptr[], int nlines)
{
    putchar('\n');
    while(nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* Qsort:   sort v[left]...v[right] into increasing order */
void Qsort(void* v[], int left, int right, int (*comp)(void*, void*), unsigned char flags)
{
    int i, last;
    void swap(void* v[], int, int);

    if(left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;

    if((flags & F_REVERSE))
    {
        for(i = left+1; i <= right; i++)
        {
            if((*comp)(v[i], v[left]) > 0)
                swap(v, ++last, i);
        }
    }
    else
    {
        for(i = left+1; i <= right; i++)
        {
            if((*comp)(v[i], v[left]) < 0)
                swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    Qsort(v, left, last-1, comp, flags);
    Qsort(v, last+1, right, comp, flags);
}

void swap(void *v[], int i, int j)
{
    void* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(const char* s1, const char* s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if(v1 < v2)
        return -1;
    else if(v1 > v2)
        return 1;
    else
        return 0;
}

int Strcmp(const char* s1, const char* s2)
{
    while(1)
    {
        while((*s1 == *s2) && (*s1 && *s2))
            s1++, s2++;

        if(IS_UPPER(*s1) || IS_UPPER(*s2))
        {
            char c1, c2;
            if((c1 = TO_LOWER(*s1)) != (c2 = TO_LOWER(*s2)))
                return (c1 > c2) ? 1 : -1;
            else
                s1++, s2++;
        }
        else
            break;
    }

    if(*s1 > * s2)
        return 1;
    else if(*s1 < *s2)
        return -1;
    else
        return 0;
}
