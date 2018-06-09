#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct activity {
    int index;
    int profit;
    int deadline;
};

struct disjoint_set {
    vector<int> parent;

    explicit disjoint_set(int n) : parent(n + 1) {
        for (int i = 0; i < parent.size(); i++) {
            parent[i] = i;
        }
    }

    int find(int s) {
        if (s == parent[s]) return s;
        return parent[s] = find(parent[s]);
    }

    int merge(int u, int v) {
        parent[v] = u;
    }

    void show() {
        for (auto x : parent) cout<<x<<" ";
    }
};

int findMaxDeadline(vector<activity> activities) {
    int max = -1;

    for (auto f : activities) {
        if (f.deadline > max) max = f.deadline;
    }

    return max;
}

vector<activity> read() {
    return {{1, 4, 3}, {2, 1, 1}, {3, 2, 1}, {4, 5, 3}};
}


vector<activity> solve(vector<activity> activities) {
    sort(activities.begin(), activities.end(), [](activity a1, activity a2) -> bool { return a1.profit > a2.profit; });
    int maxDeadline = findMaxDeadline(activities);

    disjoint_set ds(maxDeadline);

    vector<activity> sol;
    vector<int> slots;

    for (auto act : activities) {
        int slot = ds.find(act.deadline);
        if (slot > 0) {
            ds.merge(ds.find(slot - 1), slot);
            sol.push_back(act);
            slots.push_back(slot);
        }
    }

    for (auto x : slots) cout<<x<<" ";
    cout<<endl;
    return sol;
}


int main() {

    auto in = read();

    auto sol = solve(in);

    int prof = 0;

    for (auto x : sol) {
        prof += x.profit;
        cout << x.index << " ";
    }
    cout<<endl<<prof<<endl;

    return 0;
}