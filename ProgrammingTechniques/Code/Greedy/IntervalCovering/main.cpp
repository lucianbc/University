#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


bool pointInPolygon() {

    int   i, j=polyCorners-1 ;
    bool  oddNodes=NO      ;

    for (i=0; i<polyCorners; i++) {
        if (polyY[i]<y && polyY[j]>=y ||  polyY[j]<y && polyY[i]>=y) {
            if (polyX[i]+(y-polyY[i])/(polyY[j]-polyY[i])*(polyX[j]-polyX[i])<x) {
                oddNodes=!oddNodes; }
        }
        j=i;
    }

    return oddNodes; }

struct interval {
    int l, r;
};

ostream& operator<< (ostream& stream, interval i) {
    stream<<i.l<<" "<<i.r;
    return stream;
}

struct input {
    interval target;
    vector<interval> intervals;
};

input read() {
    return {
            {10, 20},
            {{9, 15}, {4, 16}, {5, 12}, {16, 21}, {11, 16}}
    };
}

vector<interval> compute(vector<interval> intervals, interval target) {
    sort(intervals.begin(), intervals.end(), [](interval i1, interval i2) -> bool { return i1.l < i2.l; });

    vector<interval> result;

    int current_left = target.l;

    for (int i = 0; i < intervals.size() && current_left <= target.r; i++) {
        if (intervals[i].r <= current_left) continue;
        if (intervals[i].l > current_left)  {
            throw -1;
        }
        interval & candidate = intervals[i];
        i++;
        while (intervals[i].l <= current_left) {
            if (intervals[i].r > candidate.r) candidate = intervals[i];
            i++;
        }
        result.push_back(candidate);
        current_left = candidate.r;
        i--;
    }

    return result;
}

int main() {
    input data = read();
    vector<interval> & intervals = data.intervals;
    interval & target = data.target;

    try {
        vector<interval> result = compute(intervals, target);
        for (auto i : result) {
            cout<<i<<endl;
        }
    } catch (int code) {
        cout<<code;
    }

    return 0;
}