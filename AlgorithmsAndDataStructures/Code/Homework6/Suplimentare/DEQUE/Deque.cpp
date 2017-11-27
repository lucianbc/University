#include "Deque.h"
#include <cstdio>

Deque* newDeque(void)
{
    Deque* l = new Deque;
    l->first = NULL;
    l->last = NULL;
    l->length = 0;
    return l;
}

void pushFront(Deque* myDeque, int val)
{
    DequeElement* newEl = new DequeElement;
    newEl->value = val;
    newEl->prev = NULL;

    if(myDeque->first == NULL)
    {
        newEl->next = NULL;
        myDeque->first = newEl;
        myDeque->last = newEl;
    }
    else
    {
        myDeque->first->prev = newEl;
        newEl->next = myDeque->first;
        myDeque->first = newEl;
    }
    myDeque->length++;
}

void pushBack(Deque* myDeque, int val)
{
     DequeElement* newEl = new DequeElement;
     newEl->value = val;
     newEl->next = NULL;
     newEl->prev = myDeque->last;

     if(myDeque->first == NULL)
     {
         myDeque->first = newEl;
         myDeque->last = newEl;
     }
     else
     {
         myDeque->last->next = newEl;
         myDeque->last = newEl;
     }
     myDeque->length++;
}

void showForward(Deque* myDeque)
{
    DequeElement* iter = myDeque->first;
    while(iter != NULL)
    {
        printf("%d ", iter->value);
        iter = iter->next;
    }
    printf("\n");
}

void showBackward(Deque* myDeque)
{
    DequeElement* iter = myDeque->last;
    while(iter != NULL)
    {
        printf("%d ", iter->value);
        iter = iter->prev;
    }
    printf("\n");
}

int popFront(Deque* myDeque)
{
    if(myDeque->first == NULL)
    {
        printf("Coada nu contine elemente!\n");
        return -1;
    }

    int valToRet = myDeque->first->value;
    DequeElement* tempPtr = myDeque->first;
    myDeque->first = myDeque->first->next;
    if(myDeque->first != NULL)
        myDeque->first->prev = NULL;
    if(myDeque->first == NULL)
        myDeque->last = NULL;
    delete tempPtr;
    myDeque->length--;
    return valToRet;
}

int popBack(Deque* myDeque)
{
    if(myDeque->last == NULL)
    {
        printf("Coada nu contine elemente!\n");
        return -1;
    }

    int valToRet = myDeque->last->value;
    DequeElement* tempPtr = myDeque->last;
    myDeque->last = myDeque->last->prev;
    if(myDeque->last == NULL)
        myDeque->first = NULL;
    if(myDeque->last != NULL)
        myDeque->last->next = NULL;
    delete tempPtr;
    myDeque->length--;
    return valToRet;
}
