#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct cube {
    int len, color;
};

bool compatible(cube bigger, cube smaller) {
    return bigger.len > smaller.len && bigger.color != smaller.color;
}

vector<cube> solve(vector<cube> cubes) {
    sort(cubes.begin(), cubes.end(), [](cube c1, cube c2) -> bool { return c1.len > c2.len; });
    vector<int> maxHeights(cubes.size(), 0);

    int maxHeight = -1;

    for (int i = 0; i < cubes.size(); i++) {
        int maxCompatibleTower = i;
        for (int j = 0; j < i; j++) {
            if (compatible(cubes[j], cubes[i]) &&
                maxHeights[maxCompatibleTower] < maxHeights[j]) {
                maxCompatibleTower = j;
            }
        }
        maxHeights[i] = maxHeights[maxCompatibleTower] + cubes[i].len;
        maxHeight = maxHeight < maxHeights[i] ? maxHeights[i] : maxHeight;
    }

    vector<cube> sol;

    for (int i = maxHeights.size() - 1; i >= 0; i--) {
        if (maxHeights[i] == maxHeight && (sol.empty() || compatible(cubes[i], sol[sol.size() - 1]))) {
            maxHeight -= cubes[i].len;
            sol.push_back(cubes[i]);
        }
    }

    return sol;
}

vector<cube> read() {
    vector<cube> boxes;
    boxes.push_back({7, 3});
    boxes.push_back({8, 3});
    boxes.push_back({10, 2});
    boxes.push_back({9, 2});
    boxes.push_back({10, 1});
    boxes.push_back({8, 1});
    boxes.push_back({5, 2});
    boxes.push_back({6, 2});

    return boxes;
}


int main() {
    vector<cube> in = read();

    vector<cube> sol = solve(in);

    for(auto c : sol) {
        cout<<c.len<<" "<<c.color<<endl;
    }

    return 0;
}