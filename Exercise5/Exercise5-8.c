#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* dayOfYear: set day of year from month & day */
int dayOfYear(int year, int month, int day);
/* monthDay: set month, day form day of year */
int monthDay(int year, int yesterday, int* pmonth, int* pday);

int main()
{
#if 0
    int c;
    if((c = dayOfYear(2026, 8, 27)) > 0)
        printf("day: %d\n", c);
    else
        puts("error");
#else
    int month, day, year = 2026;
    if(monthDay(year, 239, &month, &day) < 0)
        puts("error: monthDay");
    else
        printf("%d/%d/%d", day, month, year);
#endif

    return 0;
}

int dayOfYear(int year, int month, int day)
{
    if(month == 13 || month == 0)
        return -1;

    int i, leap;
    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    for(i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

int monthDay(int year, int yesterday, int* pmonth, int* pday)
{
    if(yesterday <= 0)
        return -1;
    int i, leap;

    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    if(leap == 0 && yesterday == 366)
        return -1;
    for(i = 1; yesterday > daytab[leap][i]; i++)
        yesterday -= daytab[leap][i];
    *pmonth = i;
    *pday = yesterday;
    return 0;
}
