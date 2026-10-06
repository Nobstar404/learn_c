#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define ARRAY_SIZE 16

int Isdigit(char*s );
int GetLine(char** s, int line);
void Sort(char** s, int pos, int max);

int main(int argc, char* argv[])
{
    int n;
    if(--argc > 0 && **++argv == '-' && Isdigit(++argv[0]))
        n = atoi(*argv);
    else
        n = 10;

    char** s = (char**)malloc(n * sizeof(char*));
    int nl = GetLine(s, n);

    printf("\n\nline: %d\nout: \n", nl);
    for(int i = 0; i < nl; i++)
    {
        printf("%s", s[i]);
        free(s[i]);
    }

    /*
    for(int i = 0; i < n; i++)
        free(s[i]);
    */
    free(s);

    return 0;
}

int Isdigit(char* s)
{
    if(*s >= '0' && *s <= '9')
        return 1;
    return 0;
}

int GetLine(char* s[], int line)
{
    int i, j, n, len, c;
    len = c = 0;

    for(i = 0; c != EOF; i++)
    {
        if(len < i) len = i;
        if(i == line) i = 0;

        s[i] = (char*)realloc(s[i], n = (ARRAY_SIZE * sizeof(char)));
        for(j = 0; ((s[i][j] = c = getchar()) != '\n') && c != EOF; j++)
        {
            if(j == n)
                s[i] = (char*)realloc(s[i], n = (2 * j * sizeof(char)));
        }
        if((n-j) <= 0)
            s[i] = realloc(s[i], n += 1);
        s[i][++j] = '\0';
    }
    s[i-1][j-1] = '\n';
    Sort(s, i, len);

    return len;
}

void Sort(char** s, int pos, int max)
{
    if(pos > max) return;
    char* tmp;
    int j;
    for( ;pos != 0; pos--)
    {
        tmp = s[0];
        for(j = 0; j != max; j++)
            s[j] = s[j+1];
        s[j-1] = tmp;
    }
}
