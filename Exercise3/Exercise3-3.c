#include <stdio.h>
#include <string.h>
#include <ctype.h>

int atoi(char s[])
{
    int i, n, sign;

    for(i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s [i] == '-') ? -1 : 1;
    if(s[i] == '+' || s[i] == '-') /* skip sign */
        i++;

    for(n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');

    return sign * n;
}

void shellsort(int v[], int n)
{
    int gap, i, j, temp;

    for(gap = n/2; gap > 0; gap /= 2)
    {
        for(i = gap; i < n; i++)
        {
            for(j = i-gap; j >= 0 && v[j] > v[j+gap]; j -= gap)
            {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
        }
    }
}

void reverse(char s[])
{
    int c, i, j;

    for(i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

void expand(char s1[], char s2[])
{
    int i, j, begin, last;
    i = j = 0;

    if(s1[0] == '-') s2[j++] = s1[i++];
    for(; s1[i] != '\0'; i++)
    {
        if(s1[i] == '-')
        {
            begin = s1[i-1];
            last = s1[i+1];
            if(begin == s2[j-1]) begin++;
        }
        else
            continue;
        for(; begin <= last; j++, begin++)
        {
            s2[j] = begin;
        }
    }
    if(s1[i-1] == '-') s2[j++] = s1[i-1];

    s2[j] = '\0';
}

int main()
{
    char* s1 = "a-z0-9-";
    char s2[1024];

    expand(s1, s2);
    printf("%s", s2);

    return 0;
}
