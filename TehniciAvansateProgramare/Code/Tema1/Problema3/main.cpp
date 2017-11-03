#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct activity {
    int index;
    int deadline;
    int profit;
};

struct disjointSet {
    vector<int> parent;

    explicit disjointSet(unsigned int n) : parent(n + 1) {
        for (int i = 0; i < parent.size(); i++) {
            parent[i] = i;
        }
    }

    int find(int s) {
        if (s == parent[s])
            return s;
        return parent[s] = find(parent[s]);
    }

    void merge(int u, int v) {
        parent[v] = u;
    }
};

vector<activity*> read(istream &in) {
    unsigned int n;
    in>>n;
    vector<activity*> activities(n);
    for (int i = 0; i < activities.size(); i++) {
        auto *a = new activity;
        in>>a->profit>>a->deadline;
        a->index = i + 1;
        activities[i] = a;
    }

    return activities;
}

void free(vector<activity*> activities) {
    for (auto a : activities) {
        delete a;
    }
}

void output(vector<activity*> activities) {
    int prof = 0;

    for (auto a : activities) prof += a->profit;

    cout<<prof<<endl;

    for (auto a : activities) {
        cout<<a->index<<" ";
    }
    cout<<endl;
}

int findMaxDeadline(vector<activity*> activities) {
    int m = -1;

    for (auto f : activities) {
        m = f->deadline > m ? f->deadline : m;
    }

    return m;
}

vector<activity *> compute(vector<activity*> activities) {
    sort(activities.begin(), activities.end(), [](activity* a1, activity* a2) -> bool { return a1->profit > a2->profit; });

    int maxDeadline = findMaxDeadline(activities);

    disjointSet ds(static_cast<unsigned int>(maxDeadline));

    vector<activity*> subs;

    for (auto act : activities) {
        int slot = ds.find(act->deadline);

        if (slot > 0) {
            ds.merge(ds.find(slot - 1), slot);
            subs.push_back(act);
        }
    }

    return subs;
}

int main() {
    ifstream fin("date.in");

    vector<activity*> activities = read(fin);

//    sort(activities.begin(), activities.end(), [](activity* a1, activity* a2) -> bool { return a1->profit > a2->profit; });

    vector<activity*> subs = compute(activities);

    output(subs);

    free(activities);
}