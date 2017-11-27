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
        printf("%d ", v[i]);
    printf("\n");
}

void selectionSort(int v[], int n)
{
    for(int i = 0; i < n-1; i++)
    {
        int minIndex = i;
        for(int scan = i + 1; scan < n; scan++)
        {
            if(v[scan] < v[minIndex])
                minIndex = scan;
        }
        interschimbare(v[i], v[minIndex]);
    }
}

int main()
{
    int v[] = {-4, 235, 95, 320, -6, -394, 0, 79};
    int n = sizeof(v)/sizeof(v[0]);

    selectionSort(v, n);

    afisare(v, n);

    return 0;
}
