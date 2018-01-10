#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef pair<char, char> char_pair;

struct key_hash {
    size_t operator()(const char_pair& k) const {
        return hash<char>()(k.first) << 8 | hash<char>()(k.second);
    }
};

struct key_equals {
    bool operator()(const char_pair& lhs, const char_pair& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

class cost {
    unordered_map<char_pair, int, key_hash, key_equals> costs;
    int default_value;
    int space_value;
public:
    cost(int default_value, int space_value) : default_value(default_value), space_value(space_value) {}

    void add_cost(char c1, char c2, int cost) {
        costs[{c1, c2}] = cost;
        costs[{c2, c1}] = cost;
    }

    int get(char c1, char c2) const {
        if (c1 == c2) return 0;
        if (c1 == '-' || c2 == '-') return space_value;
        if (costs.count({c1, c2}) == 0) return default_value;
        return costs.find({c1, c2})->second;
    }
};

int min(int a, int b, int c) {
    int min_a_b = a < b ? a : b;
    return min_a_b < c ? min_a_b : c;
}

struct align {
    string first;
    string second;
    int score;
};

align get_min_score(const string &x, const string &y, const cost& c) {
    int cols = y.length() + 1;
    int rows = x.length() + 1;

    int opt[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            opt[i][j] = i == 0 && j == 0
                        ? 0
                        : i == 0
                        ? j * c.get('-', y[j - 1])
                        : j == 0
                        ? i * c.get(x[i - 1], '-')
                        : min(
                              c.get(x[i - 1], y[j - 1]) + opt[i - 1][j - 1],
                              c.get(x[i - 1], '-') + opt[i - 1][j],
                              c.get('-', y[j - 1]) + opt[i][j - 1]
                              );
        }
    }

    string nx, ny;

    int ix = x.length(), iy = y.length();

    while (ix > 0 || iy > 0) {
        char chk_x = ix > 0 ? x[ix - 1] : '-';
        char chk_y = iy > 0 ? y[iy - 1] : '-';
        if(opt[ix][iy] == opt[ix - 1][iy - 1] + c.get(chk_x, chk_y)) {
            nx += chk_x;
            ny += chk_y;
            ix -= 1; iy -= 1;
        } else if (opt[ix][iy] == opt[ix - 1][iy] + c.get(chk_x, '-')) {
            nx += chk_x;
            ny += '-';
            ix -= 1;
        } else if (opt[ix][iy] == opt[ix][iy - 1] + c.get(chk_y, '-')) {
            nx += '-';
            ny += chk_y;
            iy -= 1;
        }
    }

    reverse(nx.begin(), nx.end());
    reverse(ny.begin(), ny.end());

    return {nx, ny, opt[rows - 1][cols - 1]};
}

int main() {
    cost c(3, 2);
    c.add_cost('A', 'C', 1);
    c.add_cost('G', 'T', 1);

    string x = "GATC";
    string y = "TCAG";

    align result = get_min_score(x, y, c);
    cout<<result.first<<endl<<result.second<<endl<<result.score<<endl;
    return 0;
}