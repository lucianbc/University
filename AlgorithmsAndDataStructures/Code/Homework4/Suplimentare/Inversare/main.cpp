#include <iostream>
#include "Lista.h"

using namespace std;

List inverseazaLista(List myList)
{
    List iList = newList();
    Node* crt = myList.head;
    while(crt != NULL)
    {
        pushFront(iList, crt->value);
        crt = crt->next;
    }
    return iList;
}

void inverseazaListaM(List& myList)
{
    if(myList.length == 0 || myList.length == 1)
        return;

    Node* oHead = myList.head;
    Node* oTail = myList.tail;

    Node* prev = myList.head;
    Node* crt = prev->next;
    prev->next = NULL;
    while(crt != NULL)
    {
        Node* nextNode = crt->next;
        Node* prevNode = crt;
        crt->next = prev;
        crt = nextNode;
        prev = prevNode;
    }
    myList.head = oTail;
    myList.tail = oHead;
}

int main()
{
    List ls = newList();
    pushBack(ls, 5);
    pushBack(ls, 19);
    pushBack(ls, -1);
    pushBack(ls, 95);
    pushBack(ls, 85);
    pushBack(ls, 22);

    showList(ls);

    inverseazaListaM(ls);

    showList(ls);

    return 0;
}
