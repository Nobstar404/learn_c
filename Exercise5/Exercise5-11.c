#include <stdio.h>
#include <stdlib.h>

int getLine(char* s, int lim);
void detab(int argc, char** argv, char* s);
void entab(int argc, char** argv, char* s);

int main(int argc, char* argv[])
{
    char s[1024];
    getLine(s, 1024);
#if 0
    detab(argc, argv, s);
#else
    entab(argc, argv, s);
    printf("helo\tworld\twoi\n");
#endif

    return 0;
}

int getLine(char* s, int lim)
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

void detab(int argc, char** argv, char* s)
{
    for(int i = 0; *s; s++, i++)
    {
        if(*s == '\t')
        {
            int c = 0;
            while(c < i && --argc > 0)
                c = atoi(*++argv);
            if(c <= 0 || c == i)
                c = i+4;
            for(i += (c -= i) - 1 ; c-- > 0; )
                putchar(' ');
        }
        else
            putchar(*s);
    }
}

void entab(int argc, char** argv, char* s)
{
    char* ps = s;
    for( ; *ps; ps++)
    {
        if(*s == ' ')
        {
            for( ; *ps == ' '; ps++)
                ;
            int i = ps -s, c = 0;
            while(--argc > 0)
            {
                if((c = atoi(*++argv)) < i)
                    putchar('\t');
                else
                {
                    c = atoi(*--argv);
                    break;
                }
            }
            ps--;
            while(++c < i)
                putchar(' ');
        }
        else
            putchar(*ps);
    }
}
