#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

struct QueueElement
{
    int val;
    QueueElement* next;
};

struct Queue
{
    int length;
    QueueElement* first;
    QueueElement* last;
};

Queue newQueue(void);

void push(int, Queue&);
int pop(Queue&);
int peek(Queue);
bool empty(Queue);
int search(int, Queue);
void afiseaza(Queue);

#endif // QUEUE_H_INCLUDED
