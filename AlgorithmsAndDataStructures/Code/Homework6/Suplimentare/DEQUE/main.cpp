#include <iostream>
#include "Deque.h"

using namespace std;

int main()
{
    Deque* myDeque = newDeque();

    pushFront(myDeque, 1);
    pushBack(myDeque, 3);

    showForward(myDeque);

    popBack(myDeque);
    popFront(myDeque);
    //cout<<"asd:\n";

    showForward(myDeque);

    pushBack(myDeque, 192);
    pushFront(myDeque, 92);

    showForward(myDeque);

    showBackward(myDeque);

    return 0;
}
