#include <stdio.h>
#include <stdbool.h>
#define MAX_CHAR 100
#define MAX_LINE 100

int getline1(char* arr);
void print(char* arr);
void print_error(char* arr, size_t i, size_t col, size_t row);
bool compare(char open, char close);
void print2(char* arr);
void check(char* arr);

int main()
{
    char array[MAX_CHAR];
    if(getline1(array) > 0)
        print(array);
    check(array);

    return 0;
}

int getline1(char* arr)
{
    int i, c;
    for(i = 0; (c = getchar()) != EOF && i != MAX_CHAR; i++)
        arr[i] = c;
    arr[i] = '\0';

    return i;
}

void print(char* arr)
{
    for(size_t j = 0; arr[j] != '\0' ;j++)
        putchar(arr[j]);
}

void print_error(char* arr, size_t i, size_t row, size_t column)
{
    printf("%s:%d:%derror: expected expression before '%c' token\n", __FILE__, row, column, arr[i]);
    i -= column-=1;

    printf("%d\t|\t", row);
    while(arr[i] != '\n')
        putchar(arr[i++]);
    printf("\n\t|\t");
    for(size_t j = 0; j < column; j++)
        printf(" ");
    printf("^\n");
}

bool compare(char open, char close)
{
    if((open == '(' || '{' || '[') && close == ';') return true;
    if(open == '(' && close == ')') return true;
    if(open == '{' && close == '}') return true;
    if(open == '[' && close == ']') return true;
    return false;
}

void print2(char* arr)
{
    char temp[MAX_LINE];
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

void check(char* arr)
{
    char temp[MAX_CHAR];
    bool inString, coment;
    size_t count, head, row, column, log[MAX_CHAR];
    row = 1;
    count = column = head = 0;
    inString = coment = false;

    for(size_t i = 0; arr[i] != '\0'; i++)
    {
        column++;
        if((coment) && arr[i] == '*' && arr[i+1] == '/') coment = !coment;
        if(arr[i] == '/' && arr[i+1] == '*') coment = !coment;
        if(coment) continue;

        if(arr[i] == '\n')
        {
            if(arr[i-1] != ';')
            {
                if((arr[i-1] != ')' && arr[i-1] != '}' && arr[i-1] != ']')
                && temp[head-1] != '(' && temp[head-1] != '{' && temp[head-1] != '[')
                {
                    log[count++] = i-1;
                    log[count++] = row;
                    log[count++] = column-1;
                }
            }
            column = 0;
            row++;
        }

        if(arr[i] == '\'')
        {
            if(arr[i+1] == '\\' && arr[i+3] == '\'')
                i+=3;
            else if(arr[i+2] == '\'')
                i+=2;
            else
            {
                    log[count++] = i-1;
                    log[count++] = row;
                    log[count++] = column-1;
            }
        }

        if(arr[i] == '"') inString = !inString;
        if(inString) continue;

        if(arr[i] == '(' || arr[i] == '{' || arr[i] == '[')
            temp[head++] = arr[i];
        if(arr[i] == ')' || arr[i] == '}' || arr[i] == ']')
        {
            if(compare(temp[head-1], arr[i]))
                head--;
            else
            {
                log[count++] = i;
                log[count++] = row;
                log[count++] = column;
            }
        }
    }
    while((head--) > 0)
        printf("%s error: expected expression before '%c' token\n", __FILE__, temp[head]);
    for(size_t j = 0; j < count; j+=3)
        print_error(arr, log[j], log[j+1], log[j+2]);
    if(inString) printf("%s warnig: missing terminating \" character\n", __FILE__);
}
