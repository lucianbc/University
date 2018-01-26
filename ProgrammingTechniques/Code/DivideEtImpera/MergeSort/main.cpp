#include <iostream>

using namespace std;

void swap(int &a, int &b) {
    a = a + b;
    b = a - b;
    a = a - b;
}

void merge_sort(int v[], int l, int r) {

    if (r - l < 0) exit(0);
    if (r == l) return;
    if (r - l == 1 && v[l] > v[r]) {
        swap(v[l], v[r]);
        return;
    }

    int m = l + (r - l) / 2;

    int l_ct = m - l + 1;
    int r_ct = r - m;

    int left[l_ct], right[r_ct];

    for (int i = 0; i < l_ct; i++) {
        left[i] = v[l + i];
    }

    for (int j = 0; j < r_ct; j++) {
        right[j] = v[m + j + 1];
    }

    merge_sort(left, 0, l_ct - 1);
    merge_sort(right, 0, r_ct - 1);

    int i = 0, j = 0;

    for(int k = 0; k < r - l + 1; k++) {
        if (left[i] < right[j]) {
            v[k] = left[i];
            i += 1;

            if (i == l_ct) {
                i -= 1;
                left[i] = 0x7fffffff;
            }
        } else {
            v[k] = right[j];
            j += 1;

            if (j == r_ct) {
                j -= 1;
                right[j] = 0x7fffffff;
            }
        }
    }
}

int main() {
    int arr[] = {12, 11, 6, 7};

    int arr_size = sizeof(arr)/sizeof(arr[0]);

    merge_sort(arr, 0, arr_size - 1);

    for (int i = 0; i < arr_size; i++) {
        cout<<arr[i]<<" ";
    }

    cout<<endl;

    return 0;
}