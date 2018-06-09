// Var 1, Ex 1
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct interval {
    int l, r;
};

struct input {
    interval goal;
    vector<interval> intervals;
};

input read() {
    input inp;

    inp.goal = {10, 20};
    inp.intervals.push_back({9, 15});
    inp.intervals.push_back({4, 16});
    inp.intervals.push_back({5, 12});
    inp.intervals.push_back({14, 21});
    inp.intervals.push_back({11, 18});

    return inp;
}

vector<interval> cover(interval goal, vector<interval> intervals) {
    vector<interval> sol;

    sort(intervals.begin(), intervals.end(), [](interval i1, interval i2) -> bool { return i1.l < i2.l; } );
    int current_left = goal.l;
    for (int i = 0; i < intervals.size(); i++) {
        if (intervals[i].r <= current_left) continue;
        if (intervals[i].l > current_left) throw -1;

        interval & candidate = intervals[i];
        i++;
        while (intervals[i].l <= current_left) {
            if (intervals[i].r > candidate.r) candidate = intervals[i];
            i++;
        }
        current_left = candidate.r;
        sol.push_back(candidate);
        i--;
    }
    return sol;
}



int main() {

    input inp = read();

    vector<interval> rez = cover(inp.goal, inp.intervals);

    for(auto i : rez) {
        cout<<i.l<<" "<<i.r<<endl;
    }

    return 0;
}