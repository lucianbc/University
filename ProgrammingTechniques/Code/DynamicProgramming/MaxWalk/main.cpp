#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max(int, int);

struct point {
    int l, c;
};

int solve(const vector<vector<int>> &a, vector<point> & sol) {
    int m = a.size(); // m lines
    int n = a[0].size(); // n cols
    int p[m][n];
    p[0][0] = a[0][0];
    for (int i = 1; i < n; i++) {
        p[0][i] = p[0][i - 1] + a[0][i];
    }
    for (int i = 1; i < m; i++) {
        p[i][0] = p[i - 1][0] + a[i][0];
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            p[i][j] = max(p[i - 1][j], p[i][j - 1]) + a[i][j];
        }
    }

    int max = p[m - 1][n - 1];
    point crt = {m - 1, n - 1};

    while (crt.l != 0 || crt.c != 0) {
        sol.push_back(crt);
        if (crt.l == 0) {
            crt.c -= 1;
            continue;
        }
        if (crt.c == 0) {
            crt.c -= 1;
            continue;
        }
        if (p[crt.l][crt.c] == p[crt.l - 1][crt.c] + a[crt.l][crt.c]) {
            crt.l -= 1;
        } else {
            crt.c -= 1;
        }
    }

    sol.push_back({0, 0});
    reverse(sol.begin(), sol.end());

    return max;
}

int max(int a, int b) {
    return a > b ? a : b;
}

ostream & operator<<(ostream & o, const point & p) {
    o<<p.l<<" "<<p.c;
}

int main() {

    vector<vector<int>> a = {{2, 1, 4}, {1, 3, 2}, {1, 6, 1}};

    vector<point> sol;

    int cost = solve(a, sol);

    cout<<cost<<endl;

    for (auto x : sol) {
        point p = {x.l + 1, x.c + 1};

        cout<<p<<endl;
    }

    return 0;
}