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

void insertionSort(int v[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int val = v[i];
        int j = i - 1;
        while(v[j] > val && j >= 0)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = val;
    }
}

int main()
{
    int v[] = {9, 54, 23, -4, 95, 0};
    int n = sizeof(v)/sizeof(v[0]);

    insertionSort(v, n);

    afisare(v, n);

    return 0;
}
