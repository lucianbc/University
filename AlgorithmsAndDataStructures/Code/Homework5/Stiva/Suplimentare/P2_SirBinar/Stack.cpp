#include <iostream>

#include "Stack.h"

Stack newStack(void)
{
    Stack s;
    s.height = 0;
    s.top = NULL;
    return s;
}

void push(Stack &s, int val)
{
    StackElement* newEl = new StackElement;
    newEl->next = s.top;
    newEl->data = val;
    s.top = newEl;
    s.height++;
}

int pop(Stack &s)
{
    if(s.top != NULL)
    {
        StackElement* newTop = s.top->next;
        int val = s.top->data;
        delete s.top;
        s.top = newTop;
        s.height--;
        return val;
    }
    std::cout<<"Stiva goala\n";
    return -1;
}

int peek(Stack& s)
{
    if(s.top != NULL)
        return s.top->data;
    std::cout<<"Stiva goala\n";
    return -1;
}

bool empty(Stack &s)
{
    return s.height == 0;
}

int search(Stack &s, int a)
{
    static int count = 0;
    if(s.height != 0)
    {
        int crt = pop(s);
        if(crt == a)
        {
            push(s, crt);
            return count;
        }
        else
        {
            count++;
            return search(s, a);
            push(s, crt);
        }
    }
    std::cout<<"Elementul nu a fost gasit\n";
    return -1;
}

void afiseaza(Stack s)
{
    if(s.height != 0)
    {
        std::cout<<pop(s)<<" ";
        afiseaza(s);
    }
}
