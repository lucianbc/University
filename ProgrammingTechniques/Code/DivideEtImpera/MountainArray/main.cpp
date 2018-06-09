#include <iostream>

using namespace std;

int search(int a[], int l, int r) {
    if (r - l < 2)
        return -1;

    int p = (l + r) / 2;

    if (a[p] > a[p - 1] && a[p] > a[p + 1]) return a[p];
    if (a[p] > a[p - 1] && a[p] < a[p + 1]) return search(a, p, r);
    return search(a, l, p);
}

int main() {
    int m[] = {4, 8, 10, 11, 5};
    int n = sizeof(m)/sizeof(m[0]);

    int h = search(m, 0, n - 1);

    cout<<h<<endl;

    return 0;
}