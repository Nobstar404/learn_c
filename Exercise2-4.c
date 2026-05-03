#include <stdio.h>

void squeeze(char* s1, char* s2)
{
    size_t j, sum, counter = 0;

    for(size_t i = 0; s2[i] != '\0'; i++)
    {
        for(j = sum = 0; s1[j] != '\0'; j++)
        {
            if(s1[j] != s2[i])
                s1[sum++] = s1[j];
            else
                counter++;
        }
    }

    s1[(sum-counter)] = '\0';
}

int main()
{
    char s1[] = "learn Exercise2-4";
    char s2[] = "aiueo";
    squeeze(s1, s2);
    printf("%s\n", s1);

    return 0;
}
