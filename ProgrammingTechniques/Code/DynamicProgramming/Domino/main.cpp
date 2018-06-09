#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct domino {
    int first, last;

    domino rotate() {
        return {last, first};
    }
};

vector<domino> read() {
    return {{1, 8}, {1, 5}, {5, 3}, {5, 2}, {4, 8}, {2, 4}, {2, 3}};
}

ostream& operator<<(ostream & o, const domino & d) {
    o<<d.first<<" "<<d.last;
    return o;
}

// if the pieces can be rotated
vector<domino> longestDominoChain2(vector<domino> pieces, int & count) {
    int len[2][pieces.size()];
    for (int i = 0; i < pieces.size(); i++) {
        len[0][i] = 1; // max length if the piece is not rotated
        len[1][i] = 1; // max length if the piece is rotated
        for (int j = 0; j < i; j++) {
            if (pieces[i].first == pieces[j].last && len[0][j] + 1 > len[0][i]) {
                len[0][i] = len[0][j] + 1;
            }
            if (pieces[i].first == pieces[j].first && len[1][j] + 1 > len[0][i]) {
                len[0][i] = len[1][j] + 1;
            }
            if (pieces[i].last == pieces[j].last && len[0][j] + 1 > len[1][i]) {
                len[1][i] = len[0][j] + 1;
            }
            if (pieces[i].last == pieces[j].first && len[1][j] + 1 > len[1][i]) {
                len[1][i] = len[1][j] + 1;
            }
        }
    }

    int maxLen = 0, maxInd = -1, rot = -1, ct = 0;

    for (int i = 0; i < pieces.size(); i++) {
        if (len[0][i] > maxLen) {
            maxInd = i;
            rot = 0;
            maxLen = len[0][i];
            ct = 0;
        }
        if (len[1][i] > maxLen) {
            maxInd = i;
            rot = 1;
            maxLen = len[1][i];
            ct = 0;
        }
        if (len[0][i] == maxLen) {
            ct += 1;
        }
        if (len[1][i] == maxLen) {
            ct += 1;
        }
    }

    count = ct;

    vector<domino> sol;

    while (maxInd >= 0) {
        if (rot == 0) {
            sol.push_back(pieces[maxInd]);
            maxLen--;
        } else {
            sol.push_back(pieces[maxInd].rotate());
            maxLen--;
        }
        while (maxInd >= 0) {
            maxInd--;
            if (sol[sol.size() - 1].first == pieces[maxInd].last && len[0][maxInd] == maxLen) {
                rot = 0;
                break;
            }
            if (sol[sol.size() - 1].first == pieces[maxInd].first && len[1][maxInd] == maxLen) {
                rot = 1;
                break;
            }
        }
    }
    return sol;
}

// if the pieces cannot be rotated
vector<domino> longestDominoChain(vector<domino> pieces, int & count) {
    vector<int> len(pieces.size(), 1);
    int maxLen = 1;
    int maxIndex = 0;
    int ct = 0;
    for (int i = 0; i < len.size(); i++) {
        int crtFirstNr = pieces[i].first;
        for (int j = 0; j < i; j++) {
            if (pieces[j].last == crtFirstNr && len[j] + 1 > len[i]) {
                len[i] = len[j] + 1;
                if (len[i] > maxLen) {
                    maxLen = len[i];
                    maxIndex = i;
                }
            }
        }
    }

    for (auto x : len) {
        ct += x == maxLen;
    }

    vector<domino> sol;

    while(maxIndex >= 0) {
        sol.push_back(pieces[maxIndex]);
        maxLen--;
        do {
            maxIndex--;
        } while (pieces[maxIndex].last != sol[sol.size() - 1].first && maxIndex >= 0 && len[maxIndex] != maxLen);
    }

    count = ct;
    return sol;
}

int main() {
    vector<domino> in = read();

    int ct = 0;

    vector<domino> sol = longestDominoChain2(in, ct);

    reverse(sol.begin(), sol.end());

    for (auto a : sol) {
        cout<<a<<endl;
    }

    cout<<ct<<endl;

    return 0;
}