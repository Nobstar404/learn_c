#include <stdio.h>
#define MAX_CHAR 100

int getline1(char* arr);
void print(char* arr);

int main()
{
    char array[MAX_CHAR];
    if(getline1(array) > 0)
        print(array);

    return 0;
}

int getline1(char* arr)
{
    int i, c;
    for(i = 0; (c = getchar()) != EOF; i++)
        arr[i] = c;
    arr[i] = '\0';

    return i;
}

void print(char* arr)
{
    bool cc, ss;
    cc = ss = false;

    for(size_t i = 0; arr[i] != '\0'; i++)
    {
        if(arr[i] == '"')
        {
            size_t j;
            for(j = i+1; arr[j] != '\0'; j++)
            {
                if(arr[j] == '"')
                {
                    ss = true;
                    break;
                }
            }
            if(ss)
            {
                while(i != j)
                {
                    putchar(arr[i]);
                    i++;
                }
            }
            ss = false;
        }
        if(arr[i] == '/' && arr[i+1] == '*') cc = true;
        if(arr[i] == '*' && arr[i+1] == '/')
        {
            cc = false;
            i += 2;
        }

        if(!cc)
            putchar(arr[i]);
    }
}
