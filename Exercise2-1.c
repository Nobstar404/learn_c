#include <stdio.h>
#include <float.h>
#include <stdint.h>
#include <limits.h>

int main()
{
    printf("CHAR_BIT: %d\n", CHAR_BIT);
    printf("CHAR_MIN: %d\nCHAR_MAX: %d\n", CHAR_MIN, CHAR_MAX);
    printf("UCHAR_MAX: %d\n", UCHAR_MAX);

    printf("SHART_MIN: %d\nSHRT_MAX: %d\n", SHRT_MIN, SHRT_MAX);
    printf("USHRT_MAX: %d\n", USHRT_MAX);

    printf("INT_MIN: %d\nINT_MAX: %d\n", INT_MIN, INT_MAX);
    printf("UINT_MAX: %u\n", UINT_MAX);

    printf("LONG_MIN: %ld\nLONG_MAX: %ld\n", LONG_MIN, LONG_MAX);
    printf("ULONG_MAX: %lu\n", ULONG_MAX);

    printf("LLONG_MIN: %lld\nLLONG_MAX: %lld\n", LLONG_MIN, LLONG_MAX);
    printf("SIZE_MAX: %lu\n", SIZE_MAX);

    printf("FLT_MIN: %f\nFLT_MAX: %f\n", FLT_MIN, FLT_MAX);
    printf("DBL_MIN: %f\nDBL_MAX: %f\n", DBL_MIN, DBL_MAX);

    return 0;
}
