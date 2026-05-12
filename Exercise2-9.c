#include <stdio.h>

int BitCount(unsigned x)
{
    int b;
    for(b = 0; x!= 0; x >>= 1)
    {
        if(x & 0x1)
            b++;
    }

    return b;
}

/*
 * Exalmple
 * x    = 12    =   1100
 * x-1  = 12-1  =   1011
 *                  ---- &
 *                  1000
 * x-1  = 8-1   =   0111
 *                  ---- &
 *                  0000
 */
int BitCount2(unsigned x)
{
    int count = 0;
    while(x != 0)
    {
        x &= (x-1);
        count++;
    }

    return count;
}

int main()
{
    printf("Bit Count: %d\n", BitCount2(214));

    return 0;
}
