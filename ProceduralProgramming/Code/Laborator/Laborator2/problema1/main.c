#include <stdio.h>
#include <stdlib.h>

void printBinary(int n)
{
    if(n != 0)
    {
        printBinary(n/2);
        printf("%d", n%2);
    }
}

int main()
{
    printBinary(13);
    return 0;
}
