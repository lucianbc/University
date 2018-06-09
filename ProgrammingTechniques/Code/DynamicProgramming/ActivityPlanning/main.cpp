#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct activity {
    int start, finish, profit;
};

ostream & operator<<(ostream& o, const activity & a) {
    o<<a.start<<" "<<a.finish<<" "<<a.profit;
}

vector<activity> read() {
    return {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
}

int max(int a, int b) {
    return a > b ? a : b;
}

vector<activity> solve(vector<activity> & activities) {
    sort(activities.begin(), activities.end(), [](activity a1, activity a2) -> bool { return a1.finish < a2.finish; });

    vector<int> profits(activities.size(), 0);
    profits[0] = activities[0].profit;

    int maxProf = -1;
    for (int i = 1; i < profits.size(); i++) {
        int includingProfit = activities[i].profit;
        int indexNotConflicting = i - 1;
        while (indexNotConflicting >= 0) {
            if (activities[indexNotConflicting].finish <= activities[i].start) {
                includingProfit += activities[indexNotConflicting].profit;
                break;
            }
            indexNotConflicting--;
        }
        profits[i] = max(profits[i - 1], includingProfit);
        maxProf = max(maxProf, profits[i]);
    }

    vector<activity> sol;

    for (int i = activities.size() - 1; i >= 0; i--) {
        if (profits[i] == maxProf) {
            sol.push_back(activities[i]);
            maxProf -= activities[i].profit;
        }
    }

    return sol;
}

int main() {

    vector<activity> acts = read();

    vector<activity> sol = solve(acts);

    int cost = 0;
    for (auto x : sol) {
        cout<<x<<endl;
        cost += x.profit;
    }

    cout<<cost<<endl;

    return 0;
}