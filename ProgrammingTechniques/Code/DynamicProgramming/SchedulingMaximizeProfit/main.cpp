#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct activity {
    int deadline, duration, profit, id;
};

vector<activity> read() {
    return {{3, 5, 3, 1}, {2, 2, 1, 2}, {3, 2, 2, 3}, {5, 4, 3, 4}};
}

void solve(vector<activity> in) {
    sort(in.begin(), in.end(), [](activity a1, activity a2) -> bool { return a1.deadline < a2.deadline; });

    vector<int> maxProfit(in.size(), 0);
    vector<int> timeOfFinish(in.size(), 0);

    maxProfit[0] = in[0].profit;
    timeOfFinish[0] = in[0].deadline;

    for (int i = 1; i < in.size(); i++) {
        int goodIndex = i;
        int tmpMaxProfit = in[i].profit;
        for (int j = 0; j < i; j++) {
            if (timeOfFinish[j] + in[i].duration <= in[i].deadline && maxProfit[j] + in[i].profit > tmpMaxProfit) {
                goodIndex = j;
                tmpMaxProfit = maxProfit[j] + in[i].profit;
            }
        }
        maxProfit[i] = maxProfit[goodIndex] + in[i].profit;
        timeOfFinish[i] = goodIndex == i ? in[i].duration : timeOfFinish[goodIndex] + in[i].duration;
    }
}

int main() {
    cout << "Hello, World!" << std::endl;
    return 0;
}