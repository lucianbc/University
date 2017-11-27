#include <stdio.h>

using namespace std;

void interschimbare(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

void afisare(int v[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ",v[i]);
    printf("\n");
}

void bubbleSort(int v[], int n)
{
    int ok = 0;
    while(!ok)
    {
        ok = 1;
        int last;
        for(int i = 0; i < n - 1; i++)
            if(v[i] > v[i+1])
            {
                ok = 0;
                interschimbare(v[i], v[i+1]);
                last = i + 1;
            }
        n = last;
    }
}

int main()
{
    int v[] = {4, 3, 2, 1, 5, 6, 7};
    int n = sizeof(v)/sizeof(v[0]);

    bubbleSort(v, n);

    afisare(v, n);

    return 0;
}
