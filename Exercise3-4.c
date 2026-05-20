#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>

void reverse(char s[])
{
    int c, i, j;

    for(i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

void iota(long long n, char s[])
{
    int i = 0;
    bool sign = (n < 0) ? true : false;

    do {
        int digit = n % 10;
        s[i++] = ((digit < 0) ? -digit : digit) + '0';
    } while((n /= 10) != 0);

    if(sign)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char buffer[1024 * 1024];
    long long n = LLONG_MIN;

    iota(n, buffer);
    printf("%s\n", buffer);

    return 0;
}
