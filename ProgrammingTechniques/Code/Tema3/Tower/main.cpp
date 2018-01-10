#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct box {
    int length;
    int color;
};

vector<box> read() {
    vector<box> boxes;
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

struct rez {
    int count;
    vector<box> tower;
};

rez build_tower(vector<box> boxes) {

    vector<box> tower;

    if (boxes.empty()) return {0, tower};

    sort(boxes.begin(), boxes.end(), [] (box b1, box b2) -> bool { return  b1.length > b2.length; });

    vector<int> max_tower_height(boxes.size(), 0);

    for (int i = 0; i < boxes.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (
                    boxes[j].length > boxes[i].length &&
                    boxes[j].color != boxes[i].color &&
                    max_tower_height[j] + boxes[i].length > max_tower_height[i]
                )
                max_tower_height[i] = boxes[i].length + max_tower_height[j];
        }
        if (max_tower_height[i] == 0) max_tower_height[i] = boxes[i].length;
    }

    int max_ind = 0;

    for (int i = 0; i < max_tower_height.size(); i++) {
        if (max_tower_height[i] > max_tower_height[max_ind]) max_ind = i;
    }

    int count = 0;

    for (auto h : max_tower_height) {
        if (h == max_tower_height[max_ind]) count += 1;
    }

    int test_ind = max_ind;

    tower.push_back(boxes[test_ind]);

    for (int crt = max_ind - 1; crt >= 0; crt--) {
        if (max_tower_height[crt] + boxes[test_ind].length == max_tower_height[test_ind]) {
            test_ind = crt;
            tower.push_back(boxes[test_ind]);
        }
    }

    reverse(tower.begin(), tower.end());

//    cout<<"rez"<<endl;
//
//    for (auto x : tower) {
//        cout<<x.length<<" "<<x.color<<endl;
//    }
    return {count, tower};
}

int main() {

    vector<box> boxes = read();

    rez rez = build_tower(boxes);

    for (auto b : rez.tower) {
        cout<<b.length<<" "<<b.color<<endl;
    }

    cout<<rez.count<<endl;

    return 0;
}