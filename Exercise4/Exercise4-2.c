#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000

int atoi(char s[]);

int main()
{
    double sum = 0, atof(char []);
    char line[MAXLINE];
    int GetLine(char line[], int max);

    sum = 0;
    while(GetLine(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));

    return 0;
}

int GetLine(char s[], int lim)
{
    int c, i = 0;

    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if(c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

double atof(char s[])
{
    double val, power;
    int i, sign, esign = 1, expand = 0;

    for(i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if(s[i] == '+' || s[i] == '-')
        i++;
    for(val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if(s[i] == '.') i++;

    for(power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if(s[i] == 'e' || s[i] == 'E')
    {
        i++;
        esign = (s[i] == '-') ? -1 : 1;
        if(s[i] == '-' || s[i] == '+') i++;

        while(isdigit(s[i]))
            expand = 10.0 * expand + (s[i++] - '0');

        if(esign > 0)
        {
            while(expand != 0)
            {
                expand--;
                power /= 10;
            }
        }
        else
        {
            while(expand != 0)
            {
                expand--;
                power *= 10;
            }
        }
    }

    return sign * val / power;
}

int atoi(char s[])
{
    double atof(char s[]);

    return (int)atof(s);
}
