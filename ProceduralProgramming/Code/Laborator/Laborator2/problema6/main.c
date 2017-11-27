#include <stdio.h>
#include <stdlib.h>

int verifica(int a, int b, int c)
{
    if(a + b > c && a + c > b && b + c > a) return 1;
    return 0;
}

int main()
{
    int p, a, b, c;

    scanf("%d", &p);

    for(a = 1; a <= p - 2; a++)
    {
        for(b = a; b <= p - a - 1; b++)
        {
            int c = p - a - b;
            if(c >= b && verifica(a, b, c))
                printf("%d, %d, %d\n", a, b, c);
        }
    }
    return 0;
}
