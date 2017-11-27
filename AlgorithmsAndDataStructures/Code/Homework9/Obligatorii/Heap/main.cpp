#include <iostream>

#define left(i) (2 * i)
#define right(i) (2 * i + 1)
#define parent(i) (i / 2)

using namespace std;

void max_heapify_down(int v[], int n, int poz)
{
    //cout<<"poz: "<<poz<<endl;
    int l = left(poz);
    int r = right(poz);
    int max = (l <= n && v[l] > v[poz]) ? l : poz;
    max = (r <= n && v[r] > v[max]) ? r : max;
    if(max != poz)
    {
        swap(v[max], v[poz]);
        max_heapify_down(v, n, max);
    }
}

void max_heapify_up(int v[], int n, int poz)
{
    int p = parent(poz);
    if(p > 0 && v[poz] > v[p])
    {
        swap(v[poz], v[p]);
        max_heapify_up(v, n, p);
    }
}

void buildHeap(int h[], int n)
{
    for(int i = n / 2; i > 0; i--)
        max_heapify_down(h, n, i);
}

int getMax(int h[], int &n)
{
    int retVal = h[1];
    swap(h[1], h[n]);
    n--;
    max_heapify_down(v, n, 1);
    return retVal;
}

int main()
{
    int heap[20] = {0, 16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    int n = 11;

    buildHeap(heap, n);

    for(int i = 1; i < n; i++)
        cout<<heap[i]<<" ";
    cout<<endl;

    heap[n++] = 20;

    max_heapify_up(heap, n, n - 1);

    for(int i = 1; i < n; i++)
        cout<<heap[i]<<" ";
    cout<<endl;

    return 0;
}
