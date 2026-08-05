#include <stdio.h>

char lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}

int main()
{
    int item = 4;
    printf("You have %d item%s.\n", item, (item<=1) ? "" : "s");

    printf("%c", lower('A'));

    return 0;
}
