#include <stdio.h>

int any(char* s1, char* s2)
{
    for(size_t i = 0; s2[i] != '\0'; i++)
    {
        for(size_t j = 0; s1[j] != '\0'; j++)
        {
            if(s2[i] == s1[j]) return j;
        }
    }

    return -1;
}

int main()
{
    char s1[] = "Exercise2-5";
    char s2[] = "risc";
    int a = any(s1, s2);

    if(a > 0)
        printf("index: %d\n", a);
    else
        puts("character not found");

    return 0;
}
