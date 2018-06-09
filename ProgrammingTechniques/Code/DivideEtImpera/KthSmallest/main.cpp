#include <iostream>

using namespace std;

void swap(int &a, int &b) {
    if (&a == &b)
        return;

    a = a + b;
    b = a - b;
    a = a - b;
}


int partition(int a[], int l, int r) {
    int i = l + 1;
    int piv = a[l];
    for (int j = l + 1; j <= r; j++) {
        if (a[j] < piv) {
            swap(a[i], a[j]);
            i += 1;
        }
    }
    swap(a[l], a[i - 1]);
    return i - 1;
}

int kthSmallest(int a[], int l, int r, int k) {
    int pos = partition(a, l, r);
    if (pos - l == k - 1)
        return a[pos];
    if (pos - l > k - 1)
        return kthSmallest(a, l, pos - 1, k);
    return kthSmallest(a, pos + 1, r, k - (pos - l + 1));
}

int main() {

    int a[] = {5, 3, 7, 9, 2, 1, 0, 66, 21};
    int n = sizeof(a)/sizeof(a[0]);

    cout<<kthSmallest(a, 0, n - 1, 8)<<endl;

    for (int i = 0; i < n; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;

    return 0;
}