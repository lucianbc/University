#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    int d;
    d = b*b - 4 * a * c;

    if(d >= 0)
    {
        printf("discriminant: %d\n", d);

        float x1, x2;

        x1 = (-b - sqrt(d))/(2*a);
        x2 = (-b + sqrt(d))/(2*a);

        printf("radacinile sunt: x1 = %f, x2 = %f\n", x1, x2);
    }
    else
        printf("Ecuatia data nu are solutii reale\n");

    return 0;
}
