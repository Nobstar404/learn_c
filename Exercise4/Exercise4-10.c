#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0'
#define BUFFERSIZE 100
#define MAXVAL 100 /* maximum depth of val stack */
#define STRINGSTREAM 'a'
#define CHECKVAR 'A'

int sign = 1;

double fmod(double, double);
void swap();
void duplicate();
void clear();

int readString(char []);
int mathFunction(char s[]);
const char* sin_c = "sin\0";
const char* exp_c = "exp\0";
const char* pow_c = "pow\0";

double varbuffer[26], v;

void getln();
char buff[MAXVAL];
int bufp = 0;

int getop(char[]);
void push(double);
double pop(void);
double read(void);

int sp = 0;
double val[MAXVAL];

void ungets(char[]);

int main()
{
    int type, var;
    double op2;
    char s[MAXOP];

    getln();
    while((type = getop(s)) != EOF)
    {
        switch(type)
        {
            case NUMBER:
                push(atof(s));
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
            case STRINGSTREAM:
                if(mathFunction(s) == 1)
                    break;
                printf("error: unknow command %s\n", s);
                break;
            case CHECKVAR:
                var = s[0];
                push(varbuffer[s[0] - 'A'] * sign);
                sign = 1;
                break;
            case '=':
                pop();
                if(!isupper(var))
                {
                    puts("error: no variable");
                    break;
                }
                v = varbuffer[var - 'A'] = read();
                break;
            case 'v':
                push(v);
                break;
            case '?':
                if(sp == 0)
                    puts("error: stack is empty\n");
                printf("\t%.8g\n", val[sp-1]);
                break;
            case '\n':
                if(sp == 0)
                    puts("error: stack is empty\n");
                printf("\t%.8g\n", val[sp-1]);
                getln();
                break;
            default:
                printf("error: unknow command %s\n", s);
                break;
        }
    }

    return EXIT_SUCCESS;
}

double fmod(double x, double y)
{
    return x-((long)(x/y) * y);
}

void swap()
{
    if(sp <= 1)
    {
        puts("error: stack is empty");
        return;
    }
    double temp = val[sp-1];
    val[sp-1] = val[sp-2];
    val[sp-2] = temp;
}

void duplicate()
{
    if(sp == 0)
    {
        puts("error: stack is empty");
        return;
    }
    double temp = val[sp-1];
    val[sp++] = temp;
}

void clear()
{
    sp = 0;
}

int readString(char s[])
{
    int i = 0;
    bufp--;
    while(islower(s[++i] = buff[++bufp]));
    s[i] = '\0';

    if(strlen(s) == 1)
        return s[0];

    return STRINGSTREAM;
}

int mathFunction(char s[])
{
    if(strcmp(s, sin_c) == 0)
        push(sin(pop()));
    else if(strcmp(s, exp_c) == 0)
        push(exp(pop()));
    else if(strcmp(s, pow_c) == 0)
    {
        double op2 = pop();
        push(pow(pop(), op2));
    }
    else
        return 0;

    return 1;
}

void getln()
{
    size_t i = bufp = 0;
    int c;
    while((buff[i++] = c = getchar()) != '\n' && c != EOF && i < MAXVAL);
    buff[i] = '\0';
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int c, i = 0;

    while((s[0] = c = buff[bufp++]) == ' ' || c == '\t');
    s[1] = '\0';

    if(c == '-')
    {
        c = buff[bufp];
        if(c == ' ' || c == '\t' || c == '\n')
            return '-';
        else if(isupper(c))
        {
            while((s[0] = c = buff[bufp++]) == ' ' || c == '\t');
            sign = -1;
        }
    }

    if(isupper(c))
        return CHECKVAR;
    if(islower(c))
        return readString(s);

    if(!isdigit(c) && c != '.')
        return c; /* not number */

    bufp--;
    if(isdigit(c)) /* collect integer part */
        while(isdigit(s[++i] = c = buff[++bufp]));
    if(c == '.') /* collect friction part */
        while (isdigit(s[++i] = c = buff[++bufp]))
            ;
    s[i] = '\0';
    return NUMBER;
}

/* push: push f onto value stack */
void push(double f)
{
    if(sp < MAXVAL)
        v = val[sp++] = f;
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

double read(void)
{
    if(sp > 0)
        return val[sp-1];
    else
    {
        puts("error: stack empty");
        return 0.0;
    }
}

//void ungets(char s[])
//{
//    int len = strlen(s);
//
//    while(len > 0)
//        ungetch(s[--len]);
//}