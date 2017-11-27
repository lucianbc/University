#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);

    printf(n&1 == 1 ? "impar" : "par");

    return 0;
}
