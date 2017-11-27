#include <iostream>

#define left(i) (2 * i)
#define right(i) (2 * i + 1)
#define parent(i) (i / 2)

using namespace std;

struct Element
{
    int prioritate;
    int valoare;
};

Element coada[101];
int sz;

void max_heapify_down(Element heap[], int n, int poz)
{
    int l = left(poz);
    int r = right(poz);
    int max;
    max = (l <= n && heap[l].prioritate >= heap[poz].prioritate) ? l : poz;
    max = (r <= n && heap[r].prioritate >= heap[max].prioritate) ? r : max;

    if(max != poz)
    {
        swap(heap[poz], heap[max]);
        max_heapify_down(heap, n, max);
    }
}

void max_heapify_up(Element heap[], int n, int poz)
{
    int p = parent(poz);

    if(p > 0 && heap[p].prioritate <= heap[poz].prioritate)
    {
        swap(heap[p], heap[poz]);
        max_heapify_up(heap, n, p);
    }
}

void buildHeap(Element heap[], int n)
{
    for(int i = n / 2; i > 0; i--)
    {
        max_heapify_down(heap, n, i);
    }
}

Element maximum(Element heap[])
{
    return heap[1];
}

Element extractMaximum(Element heap[], int &n)
{
    swap(heap[1], heap[n]);
    n--;
    max_heapify_down(heap, n, 1);
    return heap[n+1];
}

void insertElement(Element heap[], int &n, Element e)
{
    heap[++n] = e;
    max_heapify_up(heap, n, n);
}

int main()
{
    insertElement(coada, sz, {1, 6});
    insertElement(coada, sz, {5, 9});
    insertElement(coada, sz, {4, 2});
    insertElement(coada, sz, {3, 1});
    insertElement(coada, sz, {4, 12});

    while(sz > 0)
    {
        Element e = extractMaximum(coada, sz);
        cout<<e.valoare<<endl;
    }
    return 0;
}
