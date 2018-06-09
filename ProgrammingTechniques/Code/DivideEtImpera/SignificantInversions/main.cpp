#include <iostream>

using namespace std;

int merge(int arr[], int tmp[], int l, int m, int r) {
    int i = l;
    int j = m + 1;
    int k = l;

    int inversions_count = 0;

    int ii = l, jj = m + 1;
    while (ii <= m && jj <= r) {
        if (arr[ii] > 2 * arr[jj]) {
            inversions_count += m - ii + 1;
            jj++;
        } else {
            ii++;
        }
    }

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

    return inversions_count;
}

int _mergeSort(int arr[], int tmp[], int l, int r) {
    int inversions_count = 0;

    if (l < r) {
        int m = (l + r) / 2;
        inversions_count += _mergeSort(arr, tmp, l, m);
        inversions_count += _mergeSort(arr, tmp, m + 1, r);

        inversions_count += merge(arr, tmp, l, m, r);
    }
    return inversions_count;
}

int mergeSort(int arr[], int n) {
    auto * tmp = new int[n];

    int inv_ct = _mergeSort(arr, tmp, 0, n - 1);

    delete tmp;

    return inv_ct;
}

int main() {

    int a[] = {4, 8, 11, 3, 5};
    int n = sizeof(a)/ sizeof(a[0]);

    int ct = mergeSort(a, n);

    for (int i = 0; i < n; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl<<"inversions: "<<ct<<endl;



    return 0;
}