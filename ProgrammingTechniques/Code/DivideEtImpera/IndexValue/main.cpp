#include <iostream>
#include <vector>

using namespace std;

vector<int> read() {
    return {-7, -1, 0, 2, 3, 5, 7};
}

int max(int a, int b) {
    if (a < b) return b;
    return a;
}

bool intersect(int a, int b, int x, int y);

int solve(vector<int> v, int l, int r) {
    if (l > r) return -1;
    int m = l + (r - l) / 2;
    if (v[m] == m) return m;
    int m1 = -1, m2 = -1;
    if (intersect(l, m - 1, v[l], v[m - 1])) {
        m1 = solve(v, l, m - 1);
    }
    if (intersect(m + 1, r, v[m + 1], v[r])) {
        m2 = solve(v, m + 1, r);
    }

    return max(m1, m2);
}

bool intersect(int a, int b, int x, int y) {
    return x <= b && a <= y;
}


int main() {

    vector<int> in = read();

    int x = solve(in, 0, in.size() - 1);

    cout<<x;

    return 0;
}