#include <stdio.h>
#include <limits.h>
#include <string.h>

int mul16(int n)
{
    return ((n >> 4) << 4);
}

void reverse(char s[])
{
    int i, j, c;

    for(i = 0, j = strlen(s)-1; i <= j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

void itob(long long n, char a[], int b)
{
    int digit, sign, i = 0;
    sign = n;

    do {
        digit = ((n % b) < 0) ? -(n % b) : (n % b);
        a[i++] = (digit >= 10) ? ((digit - 10) + 'a') : digit + '0';
    } while(n /= b);

    if(sign < 0)
        a[i++] = '-';

    a[i] = '\0';
    reverse(a);
}

int main()
{
    char a[1024 * 1024];
    itob(LLONG_MIN, a, 16);

    printf("%s\n", a);

    return 0;
}
