#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void* foo(int x)
{
    int* b = malloc(sizeof(int));
    *b = x;
    return b;
}

int main()
{
    uint8_t val1 = 0b11111111;
    int8_t val2 = 0b11111111;

    printf("val1: %d\n", val1);
    printf("val2: %d\n", val2);

    return 0;
}
