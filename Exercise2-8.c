#include <stdio.h>
#include <limits.h>

unsigned char rightrot(unsigned x, int n)
{
    unsigned sizeBit = (sizeof(unsigned char) * CHAR_BIT);
    return  (x >> n) | (x << (sizeBit-n));
}

int main()
{
    unsigned x = 229;
    printf("rightrot: %u\n", rightrot(x, 3));

    return 0;
}
