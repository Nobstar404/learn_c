#include <stdio.h>
#include <stdint.h>


int main()
{
    int s[1024];
    printf("s[3] = %d\n", s[3]);

    for(size_t i = 0;  i < 100; i++)
        printf("s[%zu]: %d\n", i, s[i]);

    return 0;
}
