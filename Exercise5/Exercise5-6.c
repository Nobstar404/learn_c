#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <ctype.h>

#define MAXVAL 1024
char buff[MAXVAL];

int myGetline(char* s, int lim);
double atof(const char* s);
int atoi(const char* s);
char* itoa(int value, char* s);
void reverse(char* s);
int strindex(const char* src, const char* find);
void ungetch(int c);
int getch(void);
int getop(char* s);

#define BUFFERSIZE 100
char buf[BUFFERSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
#define NUMBER '0'

int main()
{
#if 0
    if(myGetline(buff, MAXVAL))
        printf("%s!\n", buff);
#elif 0
    printf("%g\n", atof("+123.45"));
#elif 0
    char* ss = itoa(INT_MAX, buff);
    printf("%s\n", ss);
#elif 0
    char s[] = "Hello, World! ]+[\0";
    reverse(s);
    printf("%s\n", s);
#elif 0
    const char* s = "hello world";
    int i = strindex(s, " wor");
    printf("i: %d!\n%s\n", i, s);
#else
    char s[1024];
    double n;
    int type;
    while((type = getop(s)) != EOF)
    {
        switch(type)
        {
            case NUMBER:
                n = atof(s);
                break;
            case '\n':
                printf("%g\n", n);
                break;
            default:
                printf("type: %c\n", type);
                break;
        }
    }
#endif

    return 0;
}

int myGetline(char* s, int lim)
{
    int i, c;

    for(i = 0; lim > 0 && (c = getchar()) != EOF && c != '\n'; lim--, i++)
        *s++ = c;
    if(c == '\n')
        *s++ = c;
    *s = '\0';

    return i;
}

double atof(const char* s)
{
    double n = 0;
    int sign, power = 1;

    while(isspace(*s))
        s++;
    sign = (*s == '-') ? -1 : 1;
    if(*s == '+' || *s == '-')
        s++;

    for( ; isdigit(*s); s++)
        n = 10 * n + (*s - '0');

    if(*s == '.')
        s++;

    for( ; isdigit(*s); s++)
    {
        power *= 10;
        n = 10 * n + (*s - '0');
    }

    return sign * n / power;
}

int atoi(const char* s)
{
    return (int)atof(s);
}

char* itoa(int value, char* s)
{
    char* p = s;
    char* f = s;
    if(value < 0)
    {
        *p++ = '-', f++;
        for( ; value; value /= 10, p++)
            *p = '0' - (value % -10);
    }
    else
        for( ; value; value /= 10, p++)
            *p = '0' + (value % 10);
    *p-- = '\0';

    /* reverse */
    char temp;
    for( ; f < p; f++, p--)
        temp = *f, *f = *p, *p = temp;

    return s;
}

void reverse(char* s)
{
    char* p = s;
    while(*p)
        p++;
    p--;

    char temp;
    for( ; s < p; s++, p--)
        temp = *p, *p = *s, *s = temp;
}

int strindex(const char* src, const char* find)
{
    int i, d;
    for(i = 0; *src && *find; i++, src++)
    {
        for(d = i; (*src == *find) && *find; src++, find++)
            ;
    }
    if(!*find)
        return d;

    return -1;
}

int getop(char* s)
{
    int c;

    while((*s = c = getch()) == ' ' || c == '\t')
        ;
    *(s+1) = '\0';

    if(!isdigit(c) && c != '.')
        return *s;

    if(isdigit(c))
        while(isdigit(*++s = c = getch()))
            ;
    if(c == '.')
        while(isdigit(*++s = c = getch()))
            ;
    *s = '\0';

    if(c != EOF)
        ungetch(c);

    return NUMBER;
}

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on iput */
{
    if(bufp >= BUFFERSIZE)
        puts("ungetch: too many characters");
    else
        buf[bufp++] = c;
}
