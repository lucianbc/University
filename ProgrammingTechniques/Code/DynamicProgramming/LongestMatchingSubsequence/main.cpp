#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool matches(string first, string last) {
    return first[first.size() - 1] == last[1] && first[first.size() - 2] == last[0];
}

void solve(vector<string> in) {
    vector<int> len(in.size(), 0);

    for (int i = 0; i < in.size(); i++) {
        int maxMatching = i;
        int maxLen = 0;
        for (int j = 0; j < i; j++) {
            if (matches(in[j], in[i]) && len[j] > maxLen) {
                maxLen = len[j];
                maxMatching = j;
            }
        }

        if (maxMatching == i) len[i] = 1;
        else len[i] = maxLen + 1;
    }

    int maxLen = 0;
    for(auto x : len) {
        if (x > maxLen) maxLen = x;
    }

    cout<<maxLen<<endl;

    vector<string> words;

    for (int i = in.size() - 1; i >= 0; i--) {
        if (len[i] == maxLen && (words.empty() || matches(in[i], words[words.size() - 1]))) {
            words.push_back(in[i]);
            maxLen--;
        }
    }

    reverse(words.begin(), words.end());

    for (auto x : words) {
        cout<<x<<endl;
    }
}

int main() {
    vector<string> in = { "masa", "carte", "sac", "teatru", "tema", "rustic", "sare" };

    solve(in);

//    cout<<matches("carte", "teatru");
    return 0;
}