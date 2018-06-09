#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct interval {
    int l, r, id;
};

vector<interval> read() {
    fstream f;
    f.open("intervale.in", ios::in);

    int n;
    f>>n;
    vector<interval> v;

    for (int i = 1; i <= n; i++) {
        int l, r;
        f>>l>>r;
        v.push_back({l, r, i});
    }

    f.close();
    return v;
}

vector<interval> solve(vector<interval> & in) {
    sort(in.begin(), in.end(), [](interval i1, interval i2) -> bool { return i1.r < i2.r; });

    vector<interval> keep;
    vector<interval> notKeep;

    for (auto &i : in) {
        if (keep.empty() || i.l > keep[keep.size() - 1].r) keep.push_back(i);
        else notKeep.push_back(i);
    }

    return notKeep;
}

int main() {
    vector<interval> in = read();

    vector<interval> sol = solve(in);

    for (auto &x : sol) {
        cout<< x.id<<endl;
    }

    return 0;
}