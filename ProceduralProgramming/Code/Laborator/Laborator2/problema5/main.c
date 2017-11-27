#include <stdio.h>
#include <stdlib.h>

int count(int c)
{
    if(c == 0)
        return 1;
    int ct = 0;
    while(c)
    {
        ct++;
        c/=10;
    }
    return ct;
}

int main()
{
    int crt, prev;

    scanf("%d", &prev);
    scanf("%d", &crt);

    while(crt != 0)
    {
        int cond = prev % count(prev);
        if(cond == crt)
            printf("(%d, %d)\n", prev, crt);
        prev = crt;
        scanf("%d", &crt);
    }

    return 0;
}
