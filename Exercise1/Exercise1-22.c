#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 80
#define TABS 8
#define MAX_COLUMN 10

struct ss
{
    int a;
};

void ssInit(struct ss* s, int x)
{
    s->a = x;
}

int getline2(char* arr, int maxLine);
void print(char* arr);
void print2(char* arr);
void copy(char* to, char* form);
void reverseCopy(char* to, char* form);
void reverse(char* arr);

int main()
{
    int len;
    int max = 0;

    char line[MAX_LINE];
    char longest[MAX_LINE];

    while((len = getline2(line, MAX_LINE)) > 0)
    {
        if(len > max)
        {
            max = len;
            copy(longest, line);
        }
    }

    print2(longest); 

    return 0;
}

int getline2(char* arr, int maxLine)
{
    int c, i;

    for(i = 0; (c = getchar()) != EOF; i++)
        arr[i] = c;
    arr[i] = '\0';
    
    return i;
}

void print2(char* arr)
{
    int i, j, col;
    bool w, isTrue;
    char buffer[MAX_LINE];
    
    i = j = col = 0;
    w = true;
    isTrue = false;
    while(!isTrue)
    {
        for(col = 0; col < MAX_COLUMN; col++)
        {
            if((buffer[col] = arr[i]) == '\0')
            {
                isTrue = true;
                break;
            }
            i++;
        }
        j = col;

        if(buffer[col-1] != '\n')
        {
            for(j = col-1; j >= 0; j--)
            {
                if(buffer[j] == ' ')
                {
                    buffer[j] = '\n';
                    i -= col-j-1;
                    w = false;
                    break;
                }
            }
        }
        if(w && buffer[col-1] != '\n')
        {
            buffer[col-1] = '-';
            buffer[col] = '\n';
            j = col;
            i--;
        }
        w = true;

        for(int jj = 0; jj <= j; jj++)
            putchar(buffer[jj]);
    }
}

void print(char* arr)
{
    int c, i, nc, ns, nt;
    c = i = nc = ns = nt = 0;
    bool nw = false;

    while((c = arr[i]) != '\0')
    {
        if(c != '\t' && c != ' ' && c != '\n')
        {
            nc++;
            nw = true;
        }
        if(nw)
        {
            ns += nt;
            nt = 0;
            while(ns >= TABS)
            {
                putchar('\t');
                ns -= TABS;
            }
            while(ns != 0)
            {
                putchar(' ');
                ns--;
            }
            putchar(c);
            nw = false;
        }
        if(c == ' ')
        {
            ns++;
        }
        else if(c == '\t')
        {
            nt += TABS;
        }
        else if(c == '\n')
        {
            putchar(c);
            nc = ns = nt = 0;
        }
        i++;
    }
    putchar('\0');
}

void copy(char* to, char* form)
{
    size_t i = 0;

    while((to[i] = form[i]) != '\0')
        i++;
}

void reverse(char* arr)
{
    int j, i = 0;
    
    while((arr[i]) != '\0') i++;
    i--;
    char temp[i];

    if(i >= 0 && arr[i] == '\n') i--;

    for(j = 0; i >= 0; j++)
    {
        temp[j] = arr[i];
        i--;
    }

    for(i = 0; i <= j; i++)
        arr[i] = temp[i];
}

void reverseCopy(char* to, char* form)
{
    int j, i = 0;
    
    while((form[i]) != '\0') i++;

    i--;
    if(i >= 0 && form[i] == '\n')
    {
        to[i] = form[i];
        i--;
    }
    
    for(j = 0; i >= 0; j++)
    {
        to[j] = form[i];
        i--;
    }
    to[j] = '\0';
}
