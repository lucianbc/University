#include <iostream>

using namespace std;

int binarrySearch(int v[], int l, int r, int val)
{
    if(l > r)
        return -1;
    int p = l + (r - l) / 2;
    if(v[p] == val)
        return p;
    else if(v[p] < val)
        return binarrySearch(v, p + 1, r, val);
    else return binarrySearch(v, l, p - 1, val);
}

void print(int v[], int n, int x, int y)
{
    int poz = binarrySearch(v, 0, n-1, x);

    if(poz == -1)
        return;

    while(v[poz] <= y)
    {
        cout<<v[poz]<<" ";
        poz++;
    }
}

int main()
{
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16};

    int n = sizeof(arr)/sizeof(arr[0]);

    int x = 6, y = 15;

    print(arr, n, x, y);

    return 0;
}
