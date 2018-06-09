#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct interval {
    int start, finish, id;
};

vector<interval> solve(vector<interval> in) {
    sort(in.begin(), in.end(), [](interval i1, interval i2) -> bool { return i1.finish < i2.finish;});
    vector<interval> sol;

    for (auto i : in) {
        if (sol.empty() || i.start >= sol[sol.size() - 1].finish) {
            sol.push_back(i);
        }
    }

    return sol;
}

int main() {
    vector<interval> in = {{1, 2, 1}, {3, 4, 2}, {0, 6, 3}, {5, 7, 4}, {8, 9, 5}, {5, 9, 6}};

    vector<interval> sol = solve(in);

    for (auto x : sol) {
        cout<<x.start<<" "<<x.finish<<" "<<x.id<<endl;
    }
    return 0;
}