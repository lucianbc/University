#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 7;
    int v[6] = {2, 3, 4, 5, 6, 7};

    int s = 0;

    int i;

    for(i = 1; i < n; i++)
    {
        s^=v[i - 1];
        s^=i;
    }

    s^=n;

    printf("%d\n", s);

    return 0;
}
