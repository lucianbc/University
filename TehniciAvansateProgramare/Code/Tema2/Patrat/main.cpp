#include <iostream>
#include <iomanip>

using namespace std;

const int max_dim = 1 << 5;

typedef unsigned char map_type;

unsigned char board[max_dim][max_dim];

struct input {
    int hl, hc, n;
};

input read() {
    return {3, 6, 3};
}

map_type piece_count = 1;

void compute(map_type [max_dim][max_dim], int, int, int, int, int, int);

void mark_piece(map_type board[max_dim][max_dim],
                int hole_line, int hole_col,
                int left_line, int left_col,
                int right_line, int right_col,
                int mark_line, int mark_col,
                map_type marker) {

    if (left_line <= hole_line && hole_line <= right_line && left_col <= hole_col && hole_col <= right_col) {
        compute(board, left_line, left_col, right_line, right_col, hole_line, hole_col);
        return;
    }
    board[mark_line][mark_col] = marker;
    compute(board, left_line, left_col, right_line, right_col, mark_line, mark_col);
}

// left line, left col, right line, right col, hole line, hole col
void compute(map_type board[max_dim][max_dim],
            int left_line, int left_col,
            int right_line, int right_col,
            int hole_line, int hole_col) {

    if (left_line == right_line || left_col == right_col)
        return;

    int mid_line = left_line + (right_line - left_line) / 2;
    int mid_col = left_col + (right_col - left_col) / 2;

    map_type a = piece_count;

    piece_count++;

    mark_piece(board, hole_line, hole_col, left_line, left_col, mid_line, mid_col, mid_line, mid_col, a); // top left
    mark_piece(board, hole_line, hole_col, left_line, mid_col + 1, mid_line, right_col, mid_line, mid_col + 1, a); // top right
    mark_piece(board, hole_line, hole_col, mid_line + 1, left_col, right_line, mid_col, mid_line + 1, mid_col, a); // bottom left
    mark_piece(board, hole_line, hole_col, mid_line + 1, mid_col + 1, right_line, right_col, mid_line + 1, mid_col + 1, a); // bottom right
}

int main() {

    int hl = 1, hc = 3;

    int dim = 1 << 3;

    compute(board, 0, 0, dim - 1, dim - 1, hl, hc);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout<<setw(2)<< + board[i][j]<<" ";
        }
        cout<<endl;
    }
}