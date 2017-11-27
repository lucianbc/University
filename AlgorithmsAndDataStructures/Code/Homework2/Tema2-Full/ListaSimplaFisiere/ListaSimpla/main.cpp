#include <iostream>
#include "Lista.h"

using namespace std;

int main()
{
    List myList = newList();

    pushFront(myList, 2);
    pushFront(myList, 3);
    pushFront(myList, 1);
    showList(myList);
    deleteByValue(myList, 2);
    deleteByValue(myList, 3);
    deleteByValue(myList, 1);
    pushFront(myList, 4);
    showList(myList);

    return 0;
}
