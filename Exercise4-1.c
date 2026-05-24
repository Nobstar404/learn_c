#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

char pattern[] = "lo";

int trim(char s[]);
int GetLine(char s[], int lim);
int StrIndex(char s[], char t[]);
int strrindex(char s[], char t[]);

int main()
{
    char line[MAXLINE];
    int index, found = 0;

    while(GetLine(line, MAXLINE) > 0)
    {
        if((index = strrindex(line, pattern)))
        {
            printf("index: %d\n", index);
            printf("%s", line);
            found++;
        }
        return found;
    }

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

int StrIndex(char s[], char t[])
{
    int i, j, k;

    for(i = 0; s[i] != '\0'; i++)
    {
        for(j=i, k=0; t[k] != '\0' && s[j]==t[k]; j++, k++)
            ;
        if(k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

int strrindex(char s[], char t[])
{
    int i, j, k;
    int last = -1;

    for(i = 0; s[i] != '\0'; i++)
    {
        for(j=i, k=0; t[k] != '\0' && s[j]==t[k]; j++, k++)
            ;
        if(k > 0 && t[k] == '\0')
            last = i;
    }
    return last;
}

int trim(char s[])
{
    int n;

    for(n = strlen(s) - 1; n >= 0; n--)
    {
        if(s[n] != ' ' && s[n] != '\n' && s[n] != '\t')
            break;
    }
    s[n+1] = '\0';

    return n;
}
