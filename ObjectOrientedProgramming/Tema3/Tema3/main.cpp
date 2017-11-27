#include <iostream>

#include "Vector.h"

using namespace std;

int main() {
    Vector<int, 10> vec;

    for(int i = 1; i <= 25; i+=2) {
        vec.pushBack(i);
    }

    vec.print();

    vec.remove(17);

    vec.print();

    return 0;
}