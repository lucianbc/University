#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

struct Node {
    int value;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
    int length;
};

List newList(void);
void pushBack(List&, int);
void pushFront(List&, int);
void insertAt(List&, int, int);
void insertBefore(List&, int, int);
void insertAfter(List&, int, int);
void showList(List);
int findByValue(List, int);
int valueAt(List, int);
int deleteAt(List, int);
int deleteByValue(List&, int);
void deleteList(List&);

#endif // LISTA_H_INCLUDED
