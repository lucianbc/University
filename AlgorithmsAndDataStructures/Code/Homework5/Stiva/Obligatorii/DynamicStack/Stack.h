#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

struct StackElement
{
    int data;
    StackElement* next;
};

struct Stack
{
    StackElement* top;
    int height;
};

Stack newStack(void);

void push(Stack&, int);

int pop(Stack&);

int peek(Stack&);

bool empty(Stack&);

int search(Stack&, int);

void afiseaza(Stack);

#endif // STACK_H_INCLUDED
