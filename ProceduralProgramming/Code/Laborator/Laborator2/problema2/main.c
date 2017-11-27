#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x, n;

    printf("Introduceti numerele x si n:\n");
    scanf("%d%d", &x, &n);

    int t = 1 << (n-1);

    printf("Bitul de pe pozitia n din scrierea binara a lui x este %d\n", (x & t) == 0);

    return 0;
}
