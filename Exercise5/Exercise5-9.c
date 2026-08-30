#include <stddef.h>
#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* dayOfYear: set day of year from month & day */
int dayOfYear(int year, int month, int day);
/* monthDay: set month, day form day of year */
int monthDay(int year, int yesterday, int* pmonth, int* pday);
/* monthName: return name of n-th month */
char* monthName(int n);

int main()
{
#if 0
    int c;
    if((c = dayOfYear(2026, 8, 27)) > 0)
        printf("day: %d\n", c);
    else
        puts("error");
#elif 0
    int month, day, year = 2026;
    if(monthDay(year, 239, &month, &day) < 0)
        puts("error: monthDay");
    else
        printf("%d/%d/%d", day, month, year);
#elif 1
    int month, day, year = 2026;
    monthDay(year, 239, &month, &day);
    char* pmonth = monthName(month);
    printf("%d/%s/%d", day, pmonth, year);
#endif

    return 0;
}

int dayOfYear(int year, int month, int day)
{
    if(month == 13 || month == 0)
        return -1;

    int leap;
    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    char* p = *(daytab+leap)+1;
    while(1 < month--)
        day += *p++;
    return day;
}

int monthDay(int year, int yesterday, int* pmonth, int* pday)
{
    if(yesterday <= 0)
        return -1;
    int leap;

    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    if(leap == 0 && yesterday == 366)
        return -1;
    char* p = *(daytab+leap)+1;
    while(yesterday > *p)
        yesterday -= *p++;
    *pmonth = p - *(daytab+leap);
    *pday = yesterday;
    return 0;
}

char* monthName(int n)
{
    static char* name[] = {
        "illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };

    return (n < 1 || n > 12) ? name[0] : name[n];
}
