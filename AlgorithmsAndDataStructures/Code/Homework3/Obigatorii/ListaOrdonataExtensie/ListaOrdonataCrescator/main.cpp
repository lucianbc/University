#include <iostream>
#include "ListaCrescatoare.h"

using namespace std;

int main()
{
    List myList = newList();

    insertOrdineCrescatoare(myList, 2);
    insertOrdineCrescatoare(myList, 2);
    insertOrdineCrescatoare(myList, 93);

    showList(myList);
    return 0;
}
