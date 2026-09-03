#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFFSIZE 1024
double buff[BUFFSIZE];
int buffp = 0;

double pop();
void push(char c);

int main(int argc, char* argv[])
{
    int c;
    double op2;

    while(--argc > 0 && (c = (*++argv)[0]))
    {
        switch(c)
        {
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                push(pop() / op2);
                break;
            default:
                if(isdigit(c))
                    push(atof(*argv));
                break;
        }
    }

    if(argc != 0)
        puts("error arguments");
    else
        printf("%g\n", pop());

    return 0;
}

void push(char c)
{
    buff[buffp++] = c;
}

double pop()
{
    if(buffp <= 0)
    {
        puts("error: pop()");
        return 0 ;
    }
    return buff[--buffp];
}
