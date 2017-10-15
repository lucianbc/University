#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>

using namespace std;

vector<int> read() {
    vector<int> elements;
    int n;
    cin>>n;
    while (n) {
        int x;
        cin>>x;
        elements.push_back(x);
        n--;
    }
    return elements;
}

set<tuple<int, int, int>> get3Sums(const vector<int> &elements) {

    set<tuple<int, int, int>> my3sums;

    for (int i = 0; i < elements.size(); i++) {
        auto l = i + 1;
        auto r = static_cast<int>(elements.size() - 1);
        while (l < r) {
            int sum = elements[i] + elements[l] + elements[r];
            if (sum == 0) {
                l += 1;
                r -= 1;
                my3sums.insert(make_tuple(elements[i], elements[l], elements[r]));
            } else if (sum < 0) l += 1;
            else r -= 1;
        }
    }
    return my3sums;
}

void print(const set<tuple<int, int, int>> &input) {
    cout<<"\nRezultat:\n";

    cout<<input.size()<<endl;
}

void print(vector<int> input) {
    for (int &it : input) {
        cout<< it <<" ";
    }
    cout<<endl;
}

int main() {
    vector<int> elements = read();

    sort(elements.begin(), elements.end());

    auto rez = get3Sums(elements);

    print(rez);

//    print(elements);

    cin.get();
    cin.get();

    return 0;
}