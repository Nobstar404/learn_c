#include <stdio.h>
#include <time.h>

int atoi(const char* s)
{
    int i, n = 0;

    for(i = 0; s[i] >= '0' && s[i] <= '9'; i++)
        n = 10 * n + (s[i] - '0');

    return n;
}

int lower(int c)
{
    if(c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}

int upper(int c)
{
    if(c >= 'A' && c <= 'Z') return c;
    if(c >= 'a' && c <= 'z')
        return c + 'A' - 'a';
    else
        return c;
}

unsigned long int next = 1;

int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int) (next/65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}

int htoi(char* s)
{
    int hex, n, i;
    hex = n = i = 0;

    if((s[i] == '0' && (s[i+1] == 'x' || s[i+1] == 'X'))) i = 2;

    for(; s[i] != '\0'; i++)
    {
        if(s[i] >= '0' && s[i] <= '9')
            hex = s[i] - '0';
        else if(s[i] >= 'A' && s[i] <= 'F')
            hex = s[i] - 'A' + 10;
        else if(s[i] >= 'a' && s[i] <= 'f')
            hex = s[i] - 'a' + 10;
        else
            break;

        n = hex + (n * 16);
    }

    return n;
}

int main()
{
    printf("0x1a: %d\n", htoi("0x1a"));
    printf("0xFF: %d\n", htoi("0xFF"));

    return 0;
}
