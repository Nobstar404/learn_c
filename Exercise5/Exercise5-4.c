#include <stdio.h>

int strend(const char* s, const char* t);

int main()
{
    const char* s1 = "hello0xff";
    const char* s2 = "0xff";

    printf("%d!\n", strend(s1, s2));

    return 0;
}

int strend(const char* s, const char* t)
{
    while(*s) s++;
    size_t i;
    for(i = 0; *t; i++, t++);

    for( ; *s == *t; s--, t--, i--)
        if(i == 0) return 1;

    return 0;
}
