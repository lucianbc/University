#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct box {
    int length;
    int color;
    int index;
};

vector<box*> read(istream& in) {

    unsigned int n, p;
    in>>n>>p;
    vector<box*> boxes(n);

    for (int i = 0; i < n; i++) {
        auto* b = new box;
        in>>b->length>>b->color;
        b->index = i + 1;
        boxes[i] = b;
    }
    return boxes;
};

void output(vector<box*> boxes) {

    int height = 0;
    for (auto x : boxes) { height += x->length; }

    cout<<height<<endl;

    for (auto x : boxes) {
        cout<<x->index<<" ";
        delete x;
    }

    cout<<endl;
}

void prel(vector<box*> &boxes) {
    sort(boxes.begin(), boxes.end(), [](const box* b1, const box* b2) -> bool { return b1->length > b2->length; });
}

bool check(const vector<box*> &currentSol, box* candidate) {
    if (currentSol.empty()) return true;
    return (*currentSol.rbegin())->length > candidate->length
           && (*currentSol.rbegin())->color != candidate->color;
}

vector<box*> greedy(vector<box*> boxes) {
    vector<box*> sol;
    prel(boxes);
    for (auto x : boxes) {
        if (check(sol, x)) sol.push_back(x);
    }
    return sol;
}

int main() {

    ifstream fin("date.in");

    vector<box*> boxes = read(fin);

    vector<box*> sol = greedy(boxes);

    output(sol);

    return 0;
}