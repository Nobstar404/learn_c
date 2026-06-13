#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0'
#define BUFFERSIZE 100
#define MAXVAL 100 /* maximum depth of val stack */

int sign = 1;

double fmod(double, double);
void swap();
void duplicate();
void clear();

int strcheck(int);
int strcmpr(int, const char[]);
typedef enum int16_t
{
    NONE = -1, SIN, EXP, POW
} MathFunction;
MathFunction fsign = NONE;
const char* sin_c = "sin\0";
const char* exp_c = "exp\0";
const char* pow_c = "pow\0";

int getop(char[]);
void push(double);
double pop(void);

int sp = 0;
double val[MAXVAL];

int getch(void);
void ungetch(int);

char buf[BUFFERSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

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
                duplicate();
                break;
            case 's':
                swap();
                break;
            case 'c':
                clear();
                break;
            case 'f':
                op2 = pop();
                if(fsign == SIN)
                    push(sin(op2));
                else if(fsign == EXP)
                    push(exp(op2));
                else if(fsign == POW)
                    push(pow(pop(), op2));
                fsign = NONE;
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

void swap()
{
    if(sp <= 1) puts("error: stack is empty");
    double temp = val[sp-1];
    val[sp-1] = val[sp-2];
    val[sp-2] = temp;
}

void duplicate()
{
    if(sp == 0) puts("error: stack is empty");
    double temp = val[sp-1];
    val[sp++] = temp;
}

void clear()
{
    if(sp == 0) puts("error: stack is empty");
    while((sp--) != 1);
}

int strcheck(int c)
{
    fsign = NONE;
    switch(c)
    {
        case 's':
            if(strcmpr(c, sin_c) == 0)
                fsign = SIN;
            break;
        case 'e':
            if(strcmpr(c, exp_c) == 0)
                fsign = EXP;
            break;
        case 'p':
            if(strcmpr(c, pow_c) == 0)
                fsign = POW;
            break;
    }
    if(fsign != NONE) return 0;

    return -1;
}

int strcmpr(int c, const char s[])
{
    int i = 1;
    while(s[i] == (c = getchar()) &&  (s[i+1] != '\0'))
        i++;
    if(s[i+1] == '\0') return 0;

    return -1;
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

    if(islower(c))
    {
        if(strcheck(c) != -1)
            return 'f';

        return c;
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
