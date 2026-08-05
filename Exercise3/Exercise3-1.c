#include <stdio.h>
#include <stddef.h>

void sort(int a[], int arrayLength)
{
    int temp;

    while(arrayLength != 0)
    {
        for(int i = 0; i < arrayLength - 1; i++)
        {
            if(a[i] > a[i+1])
            {
                temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
            }
        }
        arrayLength--;
    }

}

int binsearch(int x, int v[], int n)
{
    int high, mid, low = 0;
    high = n - 1;

    while(low <= high)
    {
        mid = (low + high) / 2;
        if(x < v[mid])
            high = mid - 1;
        else if(x > v[mid])
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

int BinSearch(int x, int v[], int n)
{
    int mid, high = n - 1 , low = 0;

    while(low < high)
    {
        mid = (low + high) / 2;
        if(x <= v[mid])
            high = mid;
        else
            low = mid + 1;
    }
    if(x == v[low]) return low;

    return -1;
}

int main()
{
    int a[1000];
    const int count = sizeof(a) / sizeof(int);
    for(int i = 0; i < count; i++)
        a[i] = i;

    int result = BinSearch(999, a, count);
    printf("%d\n", result);

    return 0;
}
