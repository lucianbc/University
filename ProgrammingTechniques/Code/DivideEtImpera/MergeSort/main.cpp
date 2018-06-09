#include <iostream>

using namespace std;

void merge(int arr[], int tmp[], int l, int m, int r) {
    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[k] = arr[i];
            k++;
            i++;
        } else {
            tmp[k] = arr[j];
            k++;
            j++;
        }
    }

    while (i <= m) {
        tmp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= r) {
        tmp[k] = arr[j];
        j++;
        k++;
    }

    for (int p = l; p <= r; p++) {
        arr[p] = tmp[p];
    }
}

void _mergeSort(int arr[], int tmp[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        _mergeSort(arr, tmp, l, m);
        _mergeSort(arr, tmp, m + 1, r);

        merge(arr, tmp, l, m, r);
    }
}

void mergeSort(int arr[], int n) {
    auto * tmp = new int[n];

    _mergeSort(arr, tmp, 0, n - 1);

    delete tmp;
}

int main() {

    int a[] = {4, 6, 8, 0, -3, 61, -32, 55};
    int n = sizeof(a)/ sizeof(a[0]);

    mergeSort(a, n);

    for (int i = 0; i < n; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;


    return 0;
}