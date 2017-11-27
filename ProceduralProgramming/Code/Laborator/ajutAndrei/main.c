#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* input = fopen("plm", "r");

    if(input == NULL)
        printf("mothafuka\n");
    else
        printf("nu crapa");

    char* val;

    int ct;
    ct = fscanf(input, "%c", val);

    printf("%d\n", ct);

    return 0;
}
