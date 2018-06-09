#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

enum operatie { insert, rm, repl, noth };

int min(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

int solve(string s1, string s2, int insertCost, int removeCost, int replaceCost, vector<string> & desc) {
    int distance[s1.size()][s2.size()];
    operatie op[s1.size()][s2.size()];
    for (int i = 0; i < s1.size(); i++) {
        distance[0][i] = i * insertCost; // to transform the first 0 characters from s1 into thr first i characters of s2, we insert them
        op[0][i] = insert;
    }
    for (int i = 0; i < s2.size(); i++) {
        distance[i][0] = i * removeCost; // to transform the first i characters from s1 into the first 0 chars of s2, we remove them
        op[i][0] = rm;
    }
    op[0][0] = noth;
    for (int i = 1; i < s1.size(); i++) {
        for (int j = 0; j < s2.size(); j++) {
            if (s1[i] == s2[j]) {
                distance[i][j] = distance[i - 1][j - 1];
                op[i][j] = noth;
            }
            else {
                int ins = insertCost + distance[i][j - 1];
                int rem = removeCost + distance[i - 1][j];
                int rep = replaceCost + distance[i - 1][j - 1];
                operatie opr;
                int ct;
                if (ins < rem) {
                    ct = ins;
                    opr = insert;
                } else {
                    ct = rem;
                    opr = rm;
                }
                if (rep < ct) {
                    ct = rep;
                    opr = repl;
                }
                op[i][j] = opr;
                distance[i][j] = ct;
            }
        }
    }


    int i = s1.size() - 1, j = s2.size() - 1;

    stringstream ss;

    while (i >= 0 || j >= 0) {
        if (op[i][j] == noth) {
            ss<<"keep "<<s1[i];
            desc.push_back(ss.str());
            ss.str("");
            i -= 1;
            j -= 1;
        } else if (op[i][j] == insert) {
            ss<<"insert "<<s2[j];
            desc.push_back(ss.str());
            ss.str("");
            j = j - 1;
        } else if (op[i][j] == rm) {
            ss<<"remove "<<s1[i];
            desc.push_back(ss.str());
            ss.str("");
            i = i - 1;
        } else {
            ss<<"replace "<<s1[i]<<" with "<<s2[j];
            desc.push_back(ss.str());
            ss.str("");
            i = i - 1;
            j = j - 1;
        }
    }

    reverse(desc.begin(), desc.end());

    return distance[s1.size() - 1][s2.size() - 1];
}

int main() {
    vector<string> desc;

    int cost = solve("antet", "carte", 1, 1, 1, desc);

    cout<<cost<<endl;

    for (auto x : desc) {
        cout<<x<<endl;
    }

    return 0;
}