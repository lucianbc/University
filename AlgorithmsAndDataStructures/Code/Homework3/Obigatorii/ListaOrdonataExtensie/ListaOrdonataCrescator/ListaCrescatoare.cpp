#include "ListaCrescatoare.h"
#include "Lista.h"

void insertOrdineCrescatoare(List &myList, int val)
{
    if(myList.length == 0 || valueAt(myList, 0) > val)
    {
        pushFront(myList, val);
    }
    else if((myList.tail)->value <= val)
    {
        pushBack(myList, val);
    }
    else
    {
        Node* crt = myList.head;
        Node* newNode = new Node;
        newNode->value = val;
        while((crt->next)->value < val)
        {
            crt = crt->next;
        }
        newNode->next = crt->next;
        crt->next = newNode;
        myList.length++;
    }
}
