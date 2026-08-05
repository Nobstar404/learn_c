#include <stdio.h>
#include <stddef.h>
#define SIZE_LINE 1000

void escape(char s[], char t[])
{
    size_t j = 0;
    for(size_t i = 0; t[i] != '\0'; i++)
    {
        switch(t[i])
        {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
        }
    }
    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    size_t j = 0;
    for(size_t i = 0; t[i] != '\0'; i++)
    {
        switch (t[i])
        {
            case '\\':
                i++;
                switch(t[i])
                {
                    case 't':
                        s[j++] = '\t';
                        break;
                    case 'n':
                        s[j++] = '\n';
                        break;
                    case 'v':
                        s[j++] = '\v';
                        break;
                    case 'a':
                        s[j++] = '\a';
                        break;
                    default:
                        s[j++] = '\\';
                        s[j++] = t[i];
                }
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
}

void ScanLine(char a[])
{
    getchar();
    int c, i = 0;
    while((c = getchar()) != EOF)
        a[i++] = c;
    a[i] = '\0';
}

int main()
{
    char text[SIZE_LINE], copy[SIZE_LINE];

    ScanLine(text);
    unescape(copy, text);
    printf("%s", copy);

    return 0;
}
