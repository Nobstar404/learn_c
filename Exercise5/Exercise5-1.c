#include <stdio.h>
#include <ctype.h>

#define BUFFERSIZE 100

void swap(int* x, int* y);

int getint(int*);
int getch(void);
void ungetch(int);

char buf[BUFFERSIZE];
int bufp = 0;

int main()
{
    int x, c, type;

    while((type = getint(&x)) != EOF)
    {
        if(type)
            printf("%d\n", x);
        else
        {
            printf("error input\n");
            while((c = getch()) != '\n' && c != EOF);
        }
    }

    return 0;
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* getint: get next integer from input into *pn */
int getint(int* pn)
{
    int c, sign;

    while(isspace(c = getch())); /* skip white space */

    sign = (c == '-') ? -1 : 1;
    if(c == '+' || c == '-')
    {
        int next = getchar();
        if(!isdigit(next))
        {
            if(next != EOF)
                ungetch(next);
            ungetch(c);
            return 0;
        }
        c = next;
    }

    if(!isdigit(c) && c != EOF)
    {
        ungetch(c);
        return 0;
    }

    for(*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

    if(c != EOF)
        ungetch(c);

    return c;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if(bufp >= BUFFERSIZE)
        puts("ungetch: too many characters");
    else
        buf[bufp++] = c;
}
