#include <stdio.h>
#include <stdlib.h> /* for atof */
#include "calc.h"

#define MAXOP 100 /* max size of operand or operator */

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
