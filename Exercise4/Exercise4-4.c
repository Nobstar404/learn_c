#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <ctype.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0'

double fmod(double, double);
int swap();
int duplicate();
int clear();

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
            case 'd':
                if(duplicate() == -1)
                    puts("error: stack is empty");
                break;
            case 's':
                if(swap() == -1)
                    puts("error: stack is empty");
                break;
            case 'c':
                if(clear() == -1)
                    puts("error: stack is empty");
                break;
            case '?':
            case '\n':
                if(sp == 0)
                    puts("error: stack is empty");
                printf("\t%.8g\n", val[sp-1]);
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

int swap()
{
    if(sp <= 1) return -1;
    double temp = val[sp-1];
    val[sp-1] = val[sp-2];
    val[sp-2] = temp;
    return 0;
}

int duplicate()
{
    if(sp == 0) return -1;
    double temp = val[sp-1];
    val[sp++] = temp;
    return 0;
}

int clear()
{
    if(sp == 0) return -1;
    while((sp--) != 1);
    return 0;
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
