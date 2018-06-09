#include <iostream>

using namespace std;

double avg(int a, int b) {
    return (a + b) / 2;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a > b ? b : a;
}

double median(int arr[], int n);

double median(int a1[], int a2[], int n) {
    if (n <= 0) return -1;
    if (n == 1) return avg(a1[0], a2[0]);
    if (n == 2) return avg(max(a1[0], a2[0]), min(a1[1], a2[1]));

    double m1 = median(a1, n);
    double m2 = median(a2, n);

    if (m1 == m2) return m1;

    if (m1 < m2) {
        if (n % 2 == 0) {
            return median(a1 + n / 2 - 1, a2, n - n / 2 + 1);
        }
        return median(a1 + n / 2, a2, n - n / 2);
    }

    if (n % 2 == 0) {
        return median(a2 + n / 2 - 1, a1, n - n / 2 + 1);
    }
    return median(a2 + n / 2, a1, n - n / 2);
}

double median(int arr[], int n) {
    if (n % 2 == 0) {
        return avg(arr[n / 2 - 1], arr[n / 2]);
    }
    return arr[n / 2];
}

int main() {
    int a1[] = {1, 2, 3, 6};
    int a2[] = {4, 6, 8, 10};

    int n = sizeof(a1)/sizeof(a1[0]);

    cout<<median(a1, a2, n);

    return 0;
}