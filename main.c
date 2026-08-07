#include <stdio.h>

int foo()
{
    static int i = 0;
    return i++;
}

int main()
{
    printf("foo(): %d\n", foo());
    printf("foo(): %d\n", foo());

    return 0;
}
