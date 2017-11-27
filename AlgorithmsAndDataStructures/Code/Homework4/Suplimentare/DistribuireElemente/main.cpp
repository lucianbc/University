#include <iostream>
#include "Lista.h"

using namespace std;

void distribuire(List& a, List& b, List& c)
{
    Node** sa = &a.head;
    Node** sb = &b.head;

    Node* ci = c.head;
    Node* cp = (c.head)->next;
    while(cp != NULL && ci != NULL)
    {
        Node* wp = cp;
        Node* wi = ci;
        if(cp->next != NULL) cp = (cp->next)->next;
        if(ci->next != NULL) ci = (ci->next)->next;

        *sa = wi;
        a.tail = wi;
        sa = &((*sa)->next);
        *sa = NULL;
        a.length++;

        *sb = wp;
        b.tail = wp;
        sb = &((*sb)->next);
        *sb = NULL;
        b.length++;
    }
    if(ci != NULL)
    {
        *sa = ci;
        a.tail = ci;
        sa = NULL;
        a.length++;

        ci = NULL;
    }
}

int main()
{
    List A = newList(), B = newList(), C = newList();

    pushBack(C, 1);
    pushBack(C, 2);
    pushBack(C, 3);
    pushBack(C, 4);
    pushBack(C, 5);
    pushBack(C, 6);

    distribuire(A, B, C);

    cout<<"A: "; showList(A);
    //cout<<"Length A: "<<A.length<<" Tail A: "<<A.tail->value<<endl;

    cout<<"B: "; showList(B);
    //cout<<"Length B: "<<B.length<<" Tail B: "<<B.tail->value<<endl;


    return 0;
}
