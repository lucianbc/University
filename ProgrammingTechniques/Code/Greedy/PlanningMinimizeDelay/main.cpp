#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct activity {
    int index, duration, deadline;
};

vector<activity> read() {
    return {{1, 1, 3}, {2, 2, 2}, {3, 3, 3}};
}

vector<activity> schedule(vector<activity> activities) {
    sort(activities.begin(), activities.end(), [](activity a1, activity a2) -> bool { return a1.deadline < a2.deadline; });
    int delay = 0;
    int time_elapsed = 0;
    for (activity a : activities) {
        time_elapsed += a.duration;
        delay = max(delay, max(0, time_elapsed - a.deadline));
    }
    cout<<delay<<endl;
    return activities;
}

int main() {
    schedule(read());

    return 0;
}