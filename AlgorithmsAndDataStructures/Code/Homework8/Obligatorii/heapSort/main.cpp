#include <iostream>

#define left(i) (2 * i)
#define right(i) (2 * i + 1)
#define parent(i) (i / 2)

using namespace std;

void max_heapify_down(int h[100], int n, int poz)
{
    int l = left(poz);
    int r = right(poz);

    int max = (l <= n && h[l] > h[poz]) ? l : poz;
    max = (r <= n && h[r] > h[max]) ? r : max;

    if(max != poz)
    {
        swap(h[poz], h[max]);
        max_heapify_down(h, n, max);
    }
}

void max_heapify_up(int h[100], int n, int poz)
{
    int p = parent(poz);
    if(p > 0 && h[p] < h[poz])
    {
        swap(h[p], h[poz]);
        max_heapify_up(h, n, p);
    }
}

void buildHeap(int h[100], int n)
{
    for(int i = n / 2; i > 0; i--)
    {
        max_heapify_down(h, n, i);
    }
}

void removeMax(int h[100], int n)
{
    swap(h[1], h[n]);
    n--;
    max_heapify_down(h, n, 1);
}

int sort(int a[100], int n)
{
    buildHeap(a, n);

    for(int i = 1; i <=n; i++)
        removeMax(a, n - i + 1);
}

void show(int v[], int n)
{
    for(int i = 1; i <= n; i++)
        cout<<v[i]<<" ";
    cout<<endl;
}

int main()
{
    int a[] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(a)/sizeof(a[0]) - 1;

    sort(a, n);

    show(a, n);

    return 0;
}
