#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct
{
    char src;
    char dest;
} Pair;

void show(int n_args, int dummy, ...)
{
    va_list l;
    va_start(l, n_args);
    for(int i = 0; i < n_args; i++)
    {
        Pair crt = va_arg(l, Pair);
        printf("%c %c\n", crt.src, crt.dest);
    }

    va_end(l);
    //printf("%c %c\n", a.src, a.dest);
}

int main()
{
    Pair arg1 = {'a', 'b'},
        arg2 = {'c', 'd'},
        arg3 = {'e', 'f'},
        dummy = {'d', 'm'};


    show(3, 4, arg1, arg2, arg3);

}
