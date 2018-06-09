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

struct point{
    int line, col;
};

ostream& operator<<(ostream & o, point pt) {
    o<<pt.line<<" "<<pt.col;
    return o;
}

point search(int element, int size) {
    if (size == 1) return {0, 0};
    size /= 2;

    point offset;

    if (element <= size * size) {
        offset = {0, size};
    } else if (element <= 2 * size * size) {
        element -= size * size;
        offset = {size, 0};
    } else if (element <= 3 * size * size) {
        element -= 2 * size * size;
        offset = {0, 0};
    } else {
        element -= 3 * size * size;
        offset = {size, size};
    }

    point pt = search(element, size);
    pt.col += offset.col;
    pt.line += offset.line;

    return pt;
}

int main() {

    int size = 4;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout<<traverse(i, j, size)<<" ";
        }
        cout<<endl;
    }

    point pt = search(5, size);

    cout<<pt.line<<" "<<pt.col<<endl;

    return 0;
}