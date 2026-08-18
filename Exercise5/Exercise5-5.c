#include <stdio.h>

void myStrncpy(char* s, const char* t, int n);
char* myStrncat(char* s, const char* t, int n);
int myStrncmp(const char* s, const char* t,int n);

int main()
{
    const char* s1 = "Hello everybody!";
    const char* t = "Hello somebody!";
    int n = 5;

#if 1
    int x = myStrncmp(s1 + 12, t + 11, n);

    if(x < 0)
        printf("first %d char of [%s] precede [%s]\n", n, s1, t);
    else if(x > 0)
        printf("first %d char of [%s] follow [%s]\n", n, s1, t);
    else
        printf("first %d char of [%s] equal [%s]\n", n, s1, t);
#endif

    return 0;
}

void myStrncpy(char* s, const char* t, int n)
{
    for( ; n > 0 && *t ; s++, t++, n--)
        *s = *t;
    *++s = '\0';

    while(n > 0)
    {
        n--;
        *++s = '\0';
    }
}

char* myStrncat(char* s, const char* t, int n)
{
    char* first = s;
    while(*s)
        s++;

    for( ; n > 0 && *t ; s++, t++, n--)
        *s = *t;
    *++s = '\0';

    return first;
}

int myStrncmp(const char* s, const char* t,int n)
{
    size_t i;
    for(i = 0; (*s == *t) && n > i; s++, t++, i++)
        ;
    if(i != n)
        return *s - *t;

    return 0;
}
