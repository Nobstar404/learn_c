#include <stdio.h>

#define number 10

#if 0
#undef MAX
#endif
#undef getchar

#define max(A, B) ((A) > (B) ? (A) : (B))
#define square(x) (x) * (x)
#define dprint(expr) printf(#expr " : %g\n", expr)
#define print_args(args) printf(#args)
#define paste(front, back) front ## back
#define swap(t, x, y) {t z = x;\
    (x) = y;\
    (y) = z;\
    }

int getchar(void);

int main()
{
#if 0
    printf("square: %d\n", square(2 + 1));
    dprint(8.0 * 5.0);
    print_args(hello\thello\n);
    const char* paste(name, 1) = "hello";
    printf("name1: %s\n", name1);
    double paste(x, y) = 4.0;
    dprint(xy);
#endif
    int x, y;
    x = 3;
    y = 9;
    printf("before: x: %d, y %d\n", x, y);
    swap(int, x, y);
    printf("after: x: %d, y %d\n", x, y);

    return 0;
}

int getchar()
{
    return 0;
}
