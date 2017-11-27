#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <cstdio>

struct Node {
    int value;
    int index;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
    int length;
    int vectorLength;
};

List newList(void);
void pushBack(List&, int, int);
void pushFront(List&, int, int);
void insertAt(List&, int, int, int);
void insertBefore(List&, int, int, int);
void insertAfter(List&, int, int, int);
void showList(List);
int findByValue(List, int);
int valueAt(List, int);
int deleteAt(List, int);
int deleteByValue(List&, int);
void deleteList(List&);

#endif // LISTA_H_INCLUDED
