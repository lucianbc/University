#include <iostream>

using namespace std;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int gcd(int v[], int l, int r) {
    if (r - l < 0) return -1;
    if (r - l == 0) return v[r];
    if (r - l == 1) return gcd(v[r], v[l]);
    int m = l + (r - l) / 2;

    return gcd(gcd(v, l, m), gcd(v, l + 1, r));
}

int main() {
    int v[] = {55, 25, 10, 15, 45};

    int n = sizeof(v)/sizeof(v[0]);

    cout<<gcd(v, 0, n - 1);

    return 0;
}