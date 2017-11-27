#include <iostream>
#include "Lista.h"

using namespace std;

List combineInOrder(List l1, List l2)
{
    List lf = newList();

    Node* s1 = l1.head;
    Node* s2 = l2.head;
    Node** sf = &lf.head;

    while(s1 != NULL && s2 != NULL)
    {
        if(s1->value < s2->value)
        {
            *sf = s1;
            lf.tail = s1;
            s1 = s1->next;
            sf = &((*sf)->next);
            l1.length--;
        }
        else
        {
            *sf = s2;
            lf.tail = s2;
            s2 = s2->next;
            sf = &((*sf)->next);
            l2.length--;
        }
        lf.length++;
    }

    Node* ls = s1 == NULL ? s2 : s1;
    *sf = ls;
    lf.length += l1.length == 0 ? l2.length : l1.length;
    lf.tail = ls == s1 ? l1.tail : l2.tail;

    return lf;
}

int main()
{
    List A = newList();
    pushBack(A, 1);
    pushBack(A, 3);
    pushBack(A, 5);

    List B = newList();
    pushBack(B, 2);
    pushBack(B, 4);
    pushBack(B, 6);


    List C = combineInOrder(A, B);

    showList(C);

    return 0;
}
