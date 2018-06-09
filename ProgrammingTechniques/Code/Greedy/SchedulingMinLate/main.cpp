// Var 1 Ex 2
// Scheduling with minimizing max lateness
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

struct activity {
    int id, duration, deadline;
};

vector<activity> read() {
    return {{1, 1, 3}, {2, 2, 2}, {3, 3, 3}};
}

// schedule activities by their deadline
vector<activity> schedule(vector<activity> activities) {
    vector<activity> v = vector<activity>(std::move(activities));
    sort(v.begin(), v.end(), [](activity a1, activity a2) -> bool { return a1.deadline < a2.deadline;});
    return v;
}

int main() {

    vector<activity> act = read();

    vector<activity> sch = schedule({{1, 1, 3}, {2, 2, 2}, {3, 3, 3}});

    int crt_time = 0;
    int total_lateness = 0;

    for(auto a : sch) {
        int lateness = crt_time + a.duration - a.deadline;
        cout << "activitatea " << a.id <<": intervalul " << crt_time << " " << crt_time + a.duration << " intarziere " <<lateness<<endl;
        crt_time += a.duration;
        total_lateness += lateness;
    }
    cout << "Intarziere planificare: " << total_lateness<<endl;

    return 0;
}