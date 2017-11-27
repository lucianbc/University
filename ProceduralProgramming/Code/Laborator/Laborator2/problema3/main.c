#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Se citesc întregii x, y, n, p. Să se copiezeze în x, începand din pozitia p,
//ultimii n biti din y și să se afișeze noua valoare a lui x.

void showBinary(int x)
{
    if(x != 0)
    {
        showBinary(x/2);
        printf("%d", x%2);
    }
}

int main()
{
    int x, y, p, n;
    //scanf("%d%d%d%d", &x, &y, &n, &p);

    x = 5256, y = 643, p = 2, n = 3;

    int n0 = n;
    int t = 0;

    showBinary(x); printf("\n");
    showBinary(y); printf("\n");

    while(n0)
    {
        t = t + pow(2, n0 - 1);
        n0--;
    }

    y = y<<(p-1);

    t = t<<(p-1);

    //showBinary(x); printf("\n");
    //showBinary(y); printf("\n");
    //showBinary(t); printf("\n");

    int xg, yg;

    xg = x & (~t);
    yg = y & t;

    //showBinary(xg); printf("\n");
    //showBinary(yg); printf("\n");

    int rez;

    rez = xg | yg;

    //showBinary(rez); printf("\n");

    x = rez;

    showBinary(x); printf("\n");

    return 0;
}
