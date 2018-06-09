#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct text {
    int id, length, frequency;
};

vector<text> read() {
    return {{1, 5, 25}, {2, 1, 25}, {3, 5, 50}};
}

vector<int> solve(vector<text> input) {
    sort(input.begin(), input.end(), [] (text t1, text t2) -> bool { return (float) t1.length / t1.frequency < (float) t2.length / t2.frequency; });
    vector<int> sol;
    for (auto t : input) {
        sol.push_back(t.id);
    }
    return sol;
}

int main() {
    vector<text> in = read();

    vector<int> sol = solve(in);

    for (auto x : sol) {
        cout<<x<<" ";
    }
    cout<<endl;

    return 0;
}