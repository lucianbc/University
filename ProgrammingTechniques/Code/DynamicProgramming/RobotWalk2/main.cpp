#include <iostream>
#include <vector>

using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}

struct point {
    int l, c;
};

vector<point> solve(vector<vector<int>> a) {
    int n = a.size();
    int m = a[0].size();
    int p[n][m];

    p[n - 1][0] = a[n - 1][0];

    for (int i = n - 2; i >= 0; i--) {
        p[i][0] = p[i + 1][0] + a[i][0];
    }

    for (int i = 1; i < m; i++) {
        p[n - 1][i] = p[n - 1][i - 1] + a[n - 1][i];
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = 1; j < m; j++) {
            p[i][j] = max(p[i + 1][j], p[i][j - 1]) + a[i][j];
        }
    }

    vector<point> sol;
    point crt = {0, m - 1};

    while(crt.l != n - 1 || crt.c != 0) {
        sol.push_back(crt);
        if (crt.l == n - 1) crt.c -= 1;
        else if (crt.c == 0) crt.l += 1;
        else {
            if (p[crt.l][crt.c] == a[crt.l][crt.c] + p[crt.l + 1][crt.c]) crt.l += 1;
            else crt.c -= 1;
        }
    }

    return sol;
}

int main() {

    vector<vector<int>> in = {{2, 8, 4}, {3, 4, 2}, {1, 6, 5}};

    vector<point> sol = solve(in);

    for (auto x : sol) {
        cout<<x.l<<" "<<x.c<<endl;
    }

    return 0;
}