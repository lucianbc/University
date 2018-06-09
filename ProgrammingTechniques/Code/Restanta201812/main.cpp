#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

typedef vector<int> line;

vector<line> read() {
    return {{2}, {12, 15}, {10, 14, 19}, {-9, -30, 12, 8}, {-8, -50, 1, 14, 9}, {99, 150, 11, 10, 9, 7}};
}

int max(int a, int b) {
    return a > b ? a : b;
}

struct point {
    int l, c;
};

struct skipable_point {
    int l, c;
    bool skip;
};

ostream& operator<<(ostream & o, const point & p) {
    o<<p.l<<" "<<p.c;
    return o;
}

ostream& operator<<(ostream & o, const skipable_point & p) {
    string tag = p.skip ? "sari" : "";
    o<<p.l + 1<<" "<<p.c + 1<<" "<<tag;
    return o;
}

vector<point> solve(vector<line> in, int & c) {
    int n = in.size();

    int p[n][n];

    for (int i = 0; i < n; i++) {
        p[i][i + 1] = INT_MIN;
    }

    p[0][0] = in[0][0];

    point max_p = {0, 0};

    for (int i = 1; i < n; i++) {
        p[i][0] = p[i - 1][0] + in[i][0];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= i; j++) {
            p[i][j] = max(p[i - 1][j - 1], p[i - 1][j]) + in[i][j];
            if (p[i][j] > p[max_p.l][max_p.c]) max_p = {i, j};
        }
    }

    vector<point> path;

    c = p[max_p.l][max_p.c];

    while (max_p.l != 0 || max_p.c != 0) {
        path.push_back(max_p);
        if (max_p.c == 0) max_p.l -= 1;
        else {
            if (p[max_p.l][max_p.c] == p[max_p.l - 1][max_p.c - 1] + in[max_p.l][max_p.c]) max_p = {max_p.l - 1, max_p.c - 1};
            else max_p = {max_p.l - 1, max_p.c};
        }
    }

    reverse(path.begin(), path.end());

    return path;

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j <= i; j++) {
//            cout<<p[i][j]<<" ";
//        }
//        cout<<endl;
//    }
}

vector<skipable_point> solve2(vector<line> in, int & c) {
    int n = in.size();

    int p[n][n][n][n];

    for (int l = 0; l < n; l++) {
        for (int c = 0; c < n; c++) {
            p[0][0][l][c] = in[0][0];

            for (int i = 0; i < n; i++) {
                p[i][i + 1][l][c] = INT_MIN;
            }

            for (int i = 1; i < n; i++) {
                p[i][0][l][c] = p[i - 1][0][l][c] + in[i][0] * (i != l || c != 0);
            }
        }
    }

    point max_p = {0, 0};

    point skip_dim = {0, 0};

    for (int l = 1; l < n; l++) {
        for (int c = 0; c < n; c++) {
            for (int i = 1; i < n; i++) {
                for (int j = 1; j <= i; j++) {
                    p[i][j][l][c] = max(p[i - 1][j - 1][l][c], p[i - 1][j][l][c]) + in[i][j];
                    if (i == l && j == c) p[i][j][l][c] -= in[i][j]; // skip if in skip dimension
                    if (p[i][j][l][c] > p[max_p.l][max_p.c][skip_dim.l][skip_dim.c]) {
                        max_p = {i, j};
                        skip_dim = {l, c};
                    }
                }
            }
        }
    }

    c = p[max_p.l][max_p.c][skip_dim.l][skip_dim.c];

//    cout<<"skip: "<<skip_dim<<endl;
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j <= i; j++) {
//            cout<<p[i][j][3][0]<<" ";
//        }
//        cout<<endl;
//    }

    vector<skipable_point> path;

    while (max_p.l != 0 || max_p.c != 0) {

        path.push_back({ max_p.l, max_p.c, max_p.l == skip_dim.l && max_p.c == skip_dim.c});

        if (max_p.c == 0) max_p.l -= 1;
        else {
            int is_skip = !(max_p.l == skip_dim.l && max_p.c == skip_dim.c);

            if (p[max_p.l][max_p.c][skip_dim.l][skip_dim.c] == p[max_p.l - 1][max_p.c - 1][skip_dim.l][skip_dim.c] + in[max_p.l][max_p.c] * is_skip)
                max_p = { max_p.l - 1, max_p.c - 1 };
            else if (p[max_p.l][max_p.c][skip_dim.l][skip_dim.c] == p[max_p.l - 1][max_p.c][skip_dim.l][skip_dim.c] + in[max_p.l][max_p.c] * is_skip)
                max_p = {max_p.l - 1, max_p.c};
            else {
                cout<<"eroare la revenire";
                break;
            }
        }
    }

    path.push_back({0, 0});

    reverse(path.begin(), path.end());

    return path;
}




int main() {

    vector<line> in = read();

//    vector<point> rez = solve(in);

    int max = 0;

    vector<skipable_point> rez = solve2(in, max);

    cout<<max<<endl;

    for (auto x : rez) {
        cout<<x<<endl;
    }

    return 0;
}