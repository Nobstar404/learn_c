#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

void foo(int s[])
{
    for(int i = 0; i < 1024; i++)
        s[i] = i;

    int* ps = s;
    for(int i = 0; i < 5; i++)
        *s++ = 4;

    for(int i = 0; i < 8; i++)
        printf("s[%d]: %d\n", i, s[i]);

    ptrdiff_t c = s-ps;
    printf("d: %td\n", c);
}

int main()
{
    int s[1024];
    foo(s);

    return 0;
}
