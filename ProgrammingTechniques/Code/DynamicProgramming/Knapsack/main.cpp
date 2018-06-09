#include <iostream>
#include <vector>

using namespace std;

struct item {
    int weight;
    int value;
};

int solve(vector<item> items, int totalWeight) {
    int K[items.size() + 1][totalWeight + 1];
    for (int i = 0; i <= items.size(); i++) {
        for (int w = 0; w <= totalWeight; w++) {
            if (i == 0 || w == 0) K[i][w] = 0;
            else if (items[i - 1].weight <= w) {
                K[i][w] = max(K[i - 1][w], items[i - 1].value + K[i - 1][w - items[i - 1].weight]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    return K[items.size()][totalWeight];
}

int main() {
    cout << "Hello, World!" << std::endl;
    return 0;
}