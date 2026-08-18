#include <stdio.h>
#include <stddef.h>

#define ALLOCSIZE 10000 /* size of available space */

size_t strlen(const char* s);

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char* allocp = allocbuf;     /* next free position */

char* alloc(int n);     /* return pointer to n characters */
void afree(char* p);    /* free storage pointed to by p */

void myStrcpy(char* s, char* t);
int myStrcmp(char* s, char* t);

void myStrcat(char* s, const char* t);

int main()
{
    char s2[1024] = "hellq";
    char* s1 = " wowrld\0";

    myStrcat(s2, s1);

    printf("s2: %s\n", s2);

    return 0;
}

size_t strlen(const char* s)
{
    const char* p = s;
    while(*p != '\0')
        p++;
    return p - s;
}

char* alloc(int n)
{
    if(allocbuf + ALLOCSIZE - allocp >= n)
    {
        allocp += n;
        return allocp - n;
    }
    else
        return 0;
}

void afree(char* p)
{
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

void myStrcpy(char* s, char* t)
{
    while((*s++ =  *t++))
        ;
}

int myStrcmp(char* s, char* t)
{
    for( ; *s == *t; s++, t++)
        if(*s == '\0')
            return 0;

    return *s - *t;
}

void myStrcat(char* s, const char* t)
{
    while(*s) s++;
    while((*s++ = *t++));
}
