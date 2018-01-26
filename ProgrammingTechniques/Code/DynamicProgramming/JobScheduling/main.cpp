// Maximize the profit in respect to the job deadlines
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct job {
    int start;
    int finish;
    int profit;
};

vector<job> read() {
    return {
            {3, 8, 3},
            {2, 4, 1},
            {3, 5, 2},
            {5, 9, 3}
    };
}

int getLatestNotConflicting(const vector<job> & jobs, int poz) {
    for (int i = poz - 1; i >=0; i--) {
        if (jobs[i].finish <= jobs[poz].start) return i;
    }
    return -1;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void compute(vector<job> & jobs) {
    sort(jobs.begin(), jobs.end(), [] (job j1, job j2) -> bool { return j1.finish < j2.finish; });

    vector<int> p(jobs.size(), 0);
    p[0] = jobs[0].profit;

    for (int i = 1; i < jobs.size(); i++) {
        int latestNotConflicting = getLatestNotConflicting(jobs, i);
        int profitIncluding = jobs[i].profit;

        if (latestNotConflicting != -1){
            profitIncluding += p[latestNotConflicting];
        }

        p[i] = max(profitIncluding, p[i - 1]);
    }

    cout<<p[jobs.size() - 1];
}

int main() {
    vector<job> jobs = read();
    compute(jobs);
    return 0;
}