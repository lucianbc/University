#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

struct DequeElement
{
    DequeElement *prev;
    DequeElement *next;
    int value;
};

struct Deque
{
    DequeElement *first;
    DequeElement *last;
    int length;
};

Deque* newDeque(void);
void pushFront(Deque*, int);
void pushBack(Deque*, int);
void showForward(Deque*);
void showBackward(Deque*);
int popFront(Deque*);
int popBack(Deque*);

#endif // DEQUE_H_INCLUDED
