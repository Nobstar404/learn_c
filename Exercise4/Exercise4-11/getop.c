#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    static int buf = ' ';
    int c, i = 0;

    if(buf != ' ' && buf != '\t')
    {
        s[0] = c = buf;
        buf = ' ';
    }
    else
        while((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';

    if(c == '-')
    {
        if((c = getch()) != ' ' || c != '\t' || c != '\n')
            s[++i] = c;
    }

    if(!isdigit(c) && c != '.')
        return s[0]; /* not number */

    if(isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if(c == '.') /* collect friction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if(c != EOF)
        buf = c;
    return NUMBER;
}
