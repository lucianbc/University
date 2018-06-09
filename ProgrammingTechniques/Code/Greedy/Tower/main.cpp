// Var 2 ex 1
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct cube {
    int id, length, color;
};

vector<cube> read() {
    return {{1, 5, 1}, {2, 10, 1}, {3, 9, 1}, {4, 8, 2}};
}

vector<cube> solve(vector<cube> cubes) {
    sort(cubes.begin(), cubes.end(), [](cube c1, cube c2) -> bool {return c1.length > c2.length;});
    vector<cube> sol;
    sol.push_back(cubes[0]);
    for (int i = 1; i < cubes.size(); i++) {
        if (cubes[i].color == sol[sol.size() - 1].color) continue;
        sol.push_back(cubes[i]);
    }
    return sol;
}

int main() {

    vector<cube> in = read();
    vector<cube> sol = solve(in);

    int h = 0;
    for (auto c : sol) h += c.length;

    cout<<h<<endl;
    for (auto c : sol) cout<<c.id<<" ";

    cout<<endl;


    return 0;
}