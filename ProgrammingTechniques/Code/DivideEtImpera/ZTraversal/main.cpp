#include <iostream>

using namespace std;

int traverse(int line, int col, int size) {
    if (size == 0) return 1;
    size /= 2;
    if (line < size && col < size) {
        //cadranul 1
        return 2 * size * size + traverse(line, col, size);
    } else if (line < size && col >= size) {
        //cadranul 2
        col = col - size;
        return traverse(line, col, size);
    } else if (line >= size && col < size) {
        //cadranul 3
        line = line - size;
        return size * size + traverse(line, col, size);

    } else {
        //cadranul 4
        line = line - size;
        col = col - size;
        return 3 * size * size + traverse(line, col, size);
    }
}

int main() {

    int size = 4;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout<<traverse(i, j, size)<<" ";
        }
        cout<<endl;
    }

    return 0;
}