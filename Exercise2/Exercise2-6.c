#include <stdio.h>

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}

unsigned CutRightBits(unsigned x, int n)
{
    return x & ~(~0 << n);
}

// ~0U means all bits turn to 1(one), for unsigned
// ~0 means -1, for signed
unsigned setbits(unsigned x, int p , int n, unsigned y)
{
    unsigned xMask = ((~0U << (p+1)) | ~(~0U << (p-n+1)));
    unsigned yPart = (y & ~(~0U << n)) << (p-n+1);
    return (x & xMask) | yPart;
}

int main()
{
    unsigned x = 100;
    unsigned y = 2;
    printf("stebits: %d\n", setbits(x, 4, 3, y));

    return 0;
}
