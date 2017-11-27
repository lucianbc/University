#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int part(int a[], int l, int r)
{
    srand(time(0));

    int poz = rand() % (r - l + 1) + l;

    int piv = l + (r - l) / 2;

    swap(a[poz], a[piv]);

    piv = a[piv];

    while(l <= r)
    {
        while(a[l] < piv) l++;
        while(a[r] > piv) r--;
        if(l <= r)
        {
            swap(a[l], a[r]);
            l++;
            r--;
        }
    }
    return l;
}

void sort(int a[], int l, int r)
{
    int p = part(a, l, r);

    if(l < p - 1)
        sort(a, l, p - 1);

    if(p < r)
        sort(a, p, r);
}

void show(int v[], int n)
{
    for(int i = 0; i < n; i++)
        cout<<v[i]<<" ";
    cout<<endl;
}

int main()
{
    int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(a)/sizeof(a[0]);

    sort(a, 0, n-1);

    show(a, n);
    return 0;
}
