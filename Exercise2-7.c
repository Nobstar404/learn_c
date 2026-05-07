#include <stdio.h>

unsigned invert(unsigned x, int p, int n)
{
    unsigned mask = ~((~0U << (p+1)) | ~(~0U << (p-n+1)));
    return x ^ mask;
}

int main()
{
    unsigned x = 170;
    printf("invert 170: %d\n", invert(x, 4, 3));

    x = 0xff;
    printf("invert 0xff: %d\n", invert(x, 7, 8));

    x = 0;
    printf("invert 0: %d\n", invert(x, 0, 1));

    x = 104;
    printf("invert 104: %d\n", invert(x, 5, 2));
 
    return 0;
}
