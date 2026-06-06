#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <ctype.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0'

double fmod(double, double);
int getop(char[]);
void push(double);
double pop(void);

#define MAXVAL 100 /* maximum depth of val stack */
int sp = 0;
double val[MAXVAL];

int getch(void);
void ungetch(int);

#define BUFFERSIZE 100
char buf[BUFFERSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int sign = 1;

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF)
    {
        switch(type)
        {
            case NUMBER:
                push(atof(s) * sign);
                sign = 1;
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                op2 = pop();
                push(pop() * op2);
                break;
            case '-':
                op2 = pop(); /* the left and right operator must be distinguished */
                push(pop() - op2);
                break;
            case '/':
                op2 = pop(); /* the left and right operator must be distinguished */
                if(op2 != 0.0) /* divison cannot be by zero */
                    push(pop() / op2);
                else
                    puts("error: zero divisor");
                break;
            case '%':
                op2 = pop();
                if(op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    puts("error: zero divisor");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknow command %s\n", s);
                break;
        }
    }

    return 0;
}

double fmod(double x, double y)
{
    return x-((long)(x/y) * y);
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if(c == '-' && sp < 2)
    {
        sign = -1;
        while((s[0] = c = getch()) == ' ' || c == '\t');
    }

    if(!isdigit(c) && c != '.')
        return c; /* not number */
    i = 0;
    if(isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if(c == '.') /* collect friction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if(c != EOF)
        ungetch(c);
    return NUMBER;
}

/* push: push f onto value stack */
void push(double f)
{
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if(sp > 0)
        return val[--sp];
    else
    {
        puts("error: stack empty");
        return 0.0;
    }
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
