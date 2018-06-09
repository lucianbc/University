#include <iostream>

using namespace std;

int merge(int arr[], int tmp[], int l, int m, int r) {
    int i, j, k;
    int inv_count = 0;

    i = l;
    j = m;
    k = l;

    while ((i <= m - 1) && (j <= r)) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
            inv_count = inv_count + (m - i);
        }
    }

    while (i <= m - 1) tmp[k++] = arr[i++];
    while (j <= r) tmp[k++] = arr[j++];

    for (i = l; i <= r; i++) arr[i] = tmp[i];

    return inv_count;
}

int _mergeSort(int arr[], int tmp[], int l, int r) {
    int mid, inv_count = 0;

    if (r > l) {
        mid = (l + r) / 2;

        inv_count = _mergeSort(arr, tmp, l, mid);
        inv_count += _mergeSort(arr, tmp, mid + 1, r);

        inv_count += merge(arr, tmp, l, mid + 1, r);
    }

    return inv_count;
}

int mergeSort(int arr[], int n) {
    auto *tmp = new int[n];
    return _mergeSort(arr, tmp, 0, n - 1);
}

int main() {

    int arr[] = {1, 20, 6, 4, 5};
    int n = sizeof(arr)/ sizeof(arr[0]);

    int inv = mergeSort(arr, n);

    cout<<inv;

    return 0;
}