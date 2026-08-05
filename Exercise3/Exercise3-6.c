#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

void reverse(char s[])
{
    int i, j, c;

    for(i = 0, j = strlen(s) - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

void itoa(long long n, char s[], int width)
{
    int i = 0;
    bool sign = (n < 0) ? true : false;

    do {
        s[i++] = ((n % 10) > 0) ? (n % 10) + '0' : -(n % 10) + '0';
    } while(n /= 10);
    if(sign) s[i++] = '-';
    s[i] = '\0';
    reverse(s);

    if(i < width)
    {
        s[width+1] = '\0';
        do {
            if(i < 0)
                s[width--] = ' ';
            else
                s[width--] = s[i--];
        } while(width >= 0);
    }
}

int main()
{
    char a[1024 * 1024];
    itoa(-128, a, 5);

    printf("%s\n", a);

    return 0;
}
