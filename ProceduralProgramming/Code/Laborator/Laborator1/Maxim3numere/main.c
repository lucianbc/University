#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a, b, c, max;

    scanf("%d%d%d", &a, &b, &c);

    max = a > b ? ( a > c ? a : c ) : ( b > c ? b : c );

    printf("maximule este: %d\n", max);

    return 0;
}
