#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int show(int n, int dummy, int a, ...)
{
    va_list list_arg;
    va_start(list_arg, n);

    for(int i = 0; i < n; i++)
    {
        int x = va_arg(list_arg, int);
        printf("%d\n", x);
    }

    va_end(list_arg);
}

int main()
{
    show(5, 1, 2, 3, 4, 5, 9);
    return 0;
}
