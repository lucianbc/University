#include <iostream>
#include "DLList.h"

using namespace std;

int main()
{
    DLList myList = newDLList();
    pushBack(myList, 1);
    pushBack(myList, 2);
    pushBack(myList, 3);
    pushBack(myList, 4);
    pushBack(myList, 5);
    pushBack(myList, 6);
    pushBack(myList, 7);
    pushBack(myList, 8);
    pushBack(myList, 9);
    pushBack(myList, 10);

    showForward(myList);
    showBackward(myList);

    deleteByIndex(myList, 9);

    deleteByValue(myList, 1);

    showForward(myList);
    showBackward(myList);

    return 0;
}
