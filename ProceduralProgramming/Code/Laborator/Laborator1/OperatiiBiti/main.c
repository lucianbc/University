#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    scanf("%d", &n);

    printf("n*8 = %d\n", n<<3);

    printf("n/4 = %d\n", n>>2);

    printf("n*10 = %d\n", (n<<3) + (n<<1));

    return 0;
}
