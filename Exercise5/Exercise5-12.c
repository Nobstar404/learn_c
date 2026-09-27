#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int GetLine(char* s, int lim);
void Detab(char* line, int argc, const char* argv[]);
void Entab(char* line, int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
    char s[1024];
    GetLine(s, 1024);

#if 0
    Detab(s, argc, argv);
#else
    Entab(s, argc, argv);
#endif

    return 0;
}

int GetLine(char* s, int lim)
{
    char* ps = s;
    int c;

    for( ; lim > 0 && (c = getchar()) != EOF && c != '\n'; lim--)
        *s++ = c;
    if(c == '\n')
        *s++ = c;
    *s = '\0';

    return s - ps;
}

void Detab(char* line, int argc, const char* argv[])
{
    int m, n;
    while(--argc > 0 && ++argv)
    {
        if(**argv == '-')
            m = atoi(++*argv);
        else if(**argv == '+')
            n = atoi(++*argv);
    }
    int lastStop = m + n;

    for(int i = 0 ; *line; line++, i++)
    {
        if(*line == '\t')
        {
            if(i > m)
            {
                while(i++ <= lastStop)
                    putchar(' ');
                lastStop += n;
            }
            else
            {
                i += 8-i;
                putchar('\t');
            }
        }
        else
            putchar(*line);
    }
}

void Entab(char* line, int argc, const char* argv[])
{
    int m, n;
    while(--argc > 0 && ++argv)
    {
        if(**argv == '-')
            m = atoi(++*argv);
        else if(**argv == '+')
            n = atoi(++*argv);
    }

    char* pline = line;
    for( ; *pline; pline++)
    {
        if(*pline == ' ')
        {
            int i;
            for(i = 0; *pline == ' '; pline++, i++)
                ;

            if((pline-line) > m)
            {
                m += i;
                for( ; i > n; i -=4)
                    putchar('\t');

                while(i--)
                    putchar(' ');
            }
            pline--;
        }
        else
            putchar(*pline);
    }
}
