#include <stdio.h>
#include <stdlib.h>

char** getCharMatrix(int n)
{
    char** a;
    a = malloc(n * sizeof(char*));

    for(int i = 0; i < n; i++)
        a[i] = malloc(n * sizeof(char));

    return a;
}

int main()
{
    int n;
    scanf("%d", &n);

    char **a = getCharMatrix(n);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            a[i][j] = 'a';
            printf("%c ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}
