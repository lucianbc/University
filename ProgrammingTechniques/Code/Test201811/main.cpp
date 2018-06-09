#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}

struct point {
    int l, c;
};

int solve(vector<vector<int>> a, int sfinal, vector<int> & costs) {
    int n = a.size(), m = a[0].size();
    int p[n][m];

    p[n - 1][0] = a[n - 1][0];

    for (int i = 1; i < m; i++) {
        p[n - 1][i] = p[n - 1][i - 1] + a[n - 1][i];
    }

    for (int i = n - 2; i >= 0; i--) {
        p[i][0] = p[i + 1][0] + a[i][0];
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = 1; j < m; j++) {
            p[i][j] = max(p[i + 1][j], p[i][j - 1]) + a[i][j];
        }
    }

    int maxDebt = p[0][m - 1];
    int crtVal = p[0][m - 1];
    point crtPoint = {0, m - 1};

    int smin = max(sfinal - crtVal, 0);

    while (crtPoint.l < n - 1 || crtPoint.c > 0) {
        costs.push_back(a[crtPoint.l][crtPoint.c]);
        crtVal -= a[crtPoint.l][crtPoint.c];
        if (crtVal < maxDebt) maxDebt = crtVal;
        if (crtPoint.c == 0) crtPoint.l += 1;
        else if (crtPoint.l == n - 1) crtPoint.c -= 1;
        else if (p[crtPoint.l][crtPoint.c] == p[crtPoint.l + 1][crtPoint.c] + a[crtPoint.l][crtPoint.c])
            crtPoint.l += 1;
        else
            crtPoint.c -= 1;
    }

    costs.push_back(a[crtPoint.l][crtPoint.c]);
    crtVal -= a[crtPoint.l][crtPoint.c];
    if (crtVal < maxDebt) maxDebt = crtVal;

    int debtCompensation = maxDebt < 0 ? 1 - maxDebt : 0;

    smin = max(debtCompensation, smin);

    reverse(costs.begin(), costs.end());

    return smin;
}

int main() {

    vector<vector<int>> in = {{20, -30, 3}, {-5, 4, 2}, {-3, -7, 1}};

    vector<int> costs;

    int smin = solve(in, 7, costs);

    cout<<smin<<endl;

    for(auto x : costs) {
        cout<<x<<" ";
    }
    cout<<endl;

    return 0;
}