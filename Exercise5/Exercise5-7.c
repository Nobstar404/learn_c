#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAXLINES 5000 // max #lines to be sorted

char* lineptr[MAXLINES]; // pointer to text lines

int readlines(char* lineptr[], int nlines,char* buff);
void writelines(char* lineptr[], int nlines);

void mQsort(char* lineptr[], int left, int right);

#define ARRAYLENGTH 1024

int main()
{
    int nlines;
    char buff[ARRAYLENGTH];

    if((nlines = readlines(lineptr, MAXLINES, buff)) >= 0)
    {
        mQsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return EXIT_SUCCESS;
    }
    else
    {
        printf("error: input too big to sort\n");
        return EXIT_FAILURE;
    }
}

#define MAXLEN 1000
int mGetline(char*, int);

int readlines(char* lineptr[], int maxlines, char* buff)
{
    int len, nlines;
    char* bufp, line[MAXLEN];

    bufp = buff;
    nlines = 0;
    while((len = mGetline(line, MAXLEN)) > 0)
    {
        if(nlines >= maxlines || (buff + ARRAYLENGTH - bufp) <= len)
            return -1;
        else
        {
            line[len-1] = '\0'; // delete newline
            strcpy(bufp, line);
            lineptr[nlines++] = bufp;
            bufp += len;
        }
    }
    return nlines;
}

void writelines(char* lineptr[], int nlines)
{
    for(size_t i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void mQsort(char* v[], int left, int right)
{
    int i, last;
    void swap(char* v[], int i, int j);

    if(left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for(i = left+1; i <= right; i++)
    {
        if(strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    mQsort(v, left, last-1);
    mQsort(v, last+1, right);
}

void swap(char* v[], int i, int j)
{
    char* temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int mGetline(char s[], int lim)
{
    int c, i = 0;

    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if(c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}
