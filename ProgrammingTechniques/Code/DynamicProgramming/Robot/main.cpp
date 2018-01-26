#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> board;

typedef pair<int, int> point;

board read() {
    return {
            {2, 8, 4},
            {3, 4, 2},
            {1, 6, 5}
    };
}

int max(int a, int b) {
    return a > b ? a : b;
}

ostream & operator<<(ostream & out, point p) {
    out<<p.first + 1<<" "<<p.second + 1;
    return out;
}


void getMax(const board & play_board) {
    auto size = static_cast<unsigned int>(play_board.size());
    point current_position = {size - 1, size - 1};
    board max_score(size, vector<int>(size, 0));
    max_score[current_position.first][current_position.second] = play_board[current_position.first][current_position.second];
    for(int i = size - 2; i >= 0; i--) {
        max_score[i][size - 1] = max_score[i + 1][size - 1] + play_board[i][size - 1];
        max_score[size - 1][i] = max_score[size - 1][i + 1] + play_board[size - 1][i];
    }
    for (int i = size - 2; i >= 0; i--) {
        for (int j = size - 2; j >= 0; j--) {
            max_score[i][j] = max(max_score[i + 1][j], max_score[i][j + 1]) + play_board[i][j];
        }
    }

    while (current_position.first != 0 || current_position.second != 0) {
        cout<<current_position<<endl;
        if (current_position.first == 0 || max_score[current_position.first][current_position.second - 1] == max_score[current_position.first][current_position.second] + play_board[current_position.first][current_position.second - 1]) { // move left
            current_position.second -= 1;
            continue;
        }
        if (current_position.second == 0 || max_score[current_position.first - 1][current_position.second] == max_score[current_position.first][current_position.second] + play_board[current_position.first - 1][current_position.second]) { // move up
            current_position.first -= 1;
            continue;
        }
    }

    cout<<current_position;
}

int main() {

    getMax(read());

    return 0;
}