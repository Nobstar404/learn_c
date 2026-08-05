#include <stdio.h>

int main()
{
    size_t i, lim = 10;
    char s[lim];
    int c = 0;

    for(i = 0; i < lim-1; i++)
    {
        s[i] = (c = getchar());
        if(c == '\n') break;
        else if(c == EOF) break;
    }

    puts("");
    for(size_t j = 0; j < i; j++)
        putchar(s[j]);

    return 0;
}
