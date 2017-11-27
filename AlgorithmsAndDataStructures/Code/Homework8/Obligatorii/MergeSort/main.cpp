#include <iostream>

using namespace std;

void sort(int a[], int l, int r)
{
    int p = l + (r - l) / 2;

    if(l < p)
        sort(a, l, p);
    if(p + 1 < r)
        sort(a, p + 1, r);

    int* tmp = new int[r - l + 1];

    int i1 = l, i2 = p + 1;

    for(int i = 0; i < r - l + 1; i++)
    {
        int v1 = i1 <= p ? a[i1] : 0x7fffffff;
        int v2 = i2 <= r ? a[i2] : 0x7fffffff;

        if(v1 < v2)
        {
            tmp[i] = v1;
            i1++;
        }
        else
        {
            tmp[i] = v2;
            i2++;
        }
    }

    for(int i = 0; i < r - l + 1; i++)
    {
        a[l + i] = tmp[i];
    }

    delete tmp;
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
