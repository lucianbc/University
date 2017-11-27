#include "DLList.h"
#include <cstdio>

DLList newDLList(void)
{
    DLList l;
    l.first = NULL;
    l.last = NULL;
    l.length = 0;
    return l;
}

void pushFront(DLList& myList, int val)
{
    ListElement* newEl = new ListElement;
    newEl->value = val;
    newEl->prev = NULL;

    if(myList.first == NULL)
    {
        newEl->next = NULL;
        myList.first = newEl;
        myList.last = newEl;
    }
    else
    {
        myList.first->prev = newEl;
        newEl->next = myList.first;
        myList.first = newEl;
    }
    myList.length++;
}

void pushBack(DLList& myList, int val)
{
     ListElement* newEl = new ListElement;
     newEl->value = val;
     newEl->next = NULL;
     newEl->prev = myList.last;

     if(myList.first == NULL)
     {
         myList.first = newEl;
         myList.last = newEl;
     }
     else
     {
         myList.last->next = newEl;
         myList.last = newEl;
     }
     myList.length++;
}

void pushAt(DLList &myList, int poz, int val)
{
    if(poz == 0)
    {
        pushFront(myList, val);
    }
    else if(poz == myList.length)
    {
        pushBack(myList, val);
    }
    else
    {
        ListElement* pozPtr;
        if(poz < myList.length / 2)
        {
            pozPtr = myList.first;
            while(poz)
            {
                pozPtr = pozPtr->next;
                poz--;
            }
        }
        else
        {
            pozPtr = myList.last;
            while(myList.length - poz - 1)
            {
                pozPtr = pozPtr->prev;
                poz++;
            }
        }

        ListElement* newEl = new ListElement;
        newEl->value = val;
        newEl->next = pozPtr;
        newEl->prev = pozPtr->prev;
        (pozPtr->prev)->next = newEl;
        pozPtr->prev = newEl;
    }
}

int deleteByIndex(DLList &myList, int poz)
{
    if(myList.first == NULL)
    {
        printf("Lista nu contine niciun element!\n");
        return -1;
    }

    ListElement* elToDel;

    if(poz == 0)
    {
        elToDel = myList.first;
        int valToRet = elToDel->value;

        if(myList.length == 1)
        {
            myList.first = NULL;
            myList.last = NULL;
            myList.length--;
            delete elToDel;
            return valToRet;
        }

        myList.first = (myList.first)->next;
        myList.first->prev = NULL;
        myList.length--;
        delete elToDel;
        return valToRet;
    }

    if(poz > myList.length - 1)
    {
        printf("Lista nu contine niciun element pe pozitia data.\n");
        return -1;
    }

    if(poz < myList.length / 2)
    {
        elToDel = myList.first;
        while(poz)
        {
            elToDel = elToDel->next;
            poz--;
        }
    }
    else
    {
        elToDel = myList.last;
        while(myList.length - poz - 1)
        {
            elToDel = elToDel->prev;
            poz++;
        }
    }

    int valToRet = elToDel->value;

    if(elToDel->next != NULL)
        (elToDel->next)->prev = elToDel->prev;
    else
        myList.last = elToDel->prev;
    (elToDel->prev)->next = elToDel->next;
    delete elToDel;
    myList.length--;
    return valToRet;
}

int deleteByValue(DLList &myList, int val)
{
    if(myList.first != NULL)
    {
        int poz = 0;
        ListElement* crt = myList.first;
        if(crt->value == val)
        {
            if(myList.first == myList.last)
            {
                myList.first = NULL;
                myList.last = NULL;
                delete crt;
                myList.length--;
                return poz;
            }
            else
            {
                myList.first = myList.first->next;
                myList.first->prev = NULL;
                delete crt;
                myList.length--;
                return poz;
            }
        }
        else
        {
            while(crt != NULL && crt->value != val)
            {
                crt = crt->next;
                poz++;
            }
            if(crt == NULL)
                return -1;
            if(crt->next != NULL)
                (crt->next)->prev = crt->prev;
            else
                myList.last = crt->prev;
            (crt->prev)->next = crt->next;
            delete crt;
            myList.length--;
            return poz;
        }
    }
    else return -1;
}

void showForward(DLList myList)
{
    while(myList.first != NULL)
    {
        printf("%d ", myList.first->value);
        myList.first = myList.first->next;
    }
    printf("\n");
}

void showBackward(DLList myList)
{
    while(myList.last != NULL)
    {
        printf("%d ", myList.last->value);
        myList.last = myList.last->prev;
    }
    printf("\n");
}
