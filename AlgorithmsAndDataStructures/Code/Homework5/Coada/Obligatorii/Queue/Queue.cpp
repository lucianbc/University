#include "Queue.h"
#include <iostream>

Queue newQueue()
{
    Queue q;
    q.first = NULL;
    q.last = NULL;
    q.length = 0;
    return q;
}

void push(int val, Queue& q)
{
    QueueElement* el = new QueueElement;
    el->next = NULL;
    el->val = val;

    q.length++;

    if(q.first == NULL)
    {
        q.first = el;
    }
    else
    {
        q.last->next = el;
    }
    q.last = el;
}

int pop(Queue &q)
{
    if(q.length != 0)
    {
        QueueElement* temp = q.first;

        if(q.first == q.last)
            q.last = NULL;

        q.first = q.first->next;

        int v = temp->val;

        delete temp;

        q.length--;

        return v;
    }

    std::cout<<"Coada nu contine elemente";
    return -1;
}

int peek(Queue q)
{
    if(q.length != 0)
        return q.first->val;
    std::cout<<"Coada nu contine elemente";
    return -1;
}

bool empty(Queue q)
{
    return q.length == 0;
}

int search(int val, Queue q)
{
    int c = 0;
    while(q.first != NULL)
    {
        if(q.first->val == val)
            return c;
        q.first = q.first->next;
        c++;
    }
    return -1;
}

void afiseaza(Queue q)
{
    while(q.first != NULL)
    {
        std::cout<<q.first->val<<" ";
        q.first = q.first->next;
    }
}
