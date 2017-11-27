#include <stdio.h>

using namespace std;

int binarySearch(int v[], int l, int r, int toFind)
{
    if(l <= r)
    {
        int piv = (l + r)/2;
        if(v[piv] == toFind)
            return piv;
        else if (v[piv] < toFind)
            return binarySearch(v, piv + 1, r, toFind);
        else if (v[piv] > toFind) return binarySearch(v, l, piv - 1, toFind);
    }
    return -1;
}

int binarySearch(int v[], int n, int toFind)
{
    int l = 0, r = n - 1;

    while(l <= r)
    {
        int piv = (l + r) / 2;
        if(v[piv] == toFind)
            return piv;
        else if (v[piv] < toFind)
            l = piv + 1;
        else if (v[piv] < toFind)
            r = piv - 1;
    }
    return -1;
}

int main()
{
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 10};
    int n = sizeof(v)/sizeof(v[0]);

    //int poz = binarySearch(v, 0, n-1, 10);

    int poz = binarySearch(v, n, 8);

    if(poz == -1)
        printf("Elementul cautat nu a fost gasit!");
    else
        printf("Elementul cautat a fost gasit pe pozitia %d", poz + 1);

    return 0;
}
