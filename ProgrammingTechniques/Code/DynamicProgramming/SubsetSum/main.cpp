#include <iostream>

using namespace std;

void subsetSum(int set[], int n, int sum) {
    bool subset[n][sum + 1];
    subset[0][0] = true;

    for (int i = 1; i < n; i++) {
        subset[i][0] = true;
    }

    for (int i = 0; i < sum; i++) {
        subset[0][i] = false;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < set[i - 1]) {
                subset[i][j] = subset[i- 1][j];
            } else {
                subset[i][j] = subset[i - 1][j] || subset[i - 1][j - set[i - 1]];
            }
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}