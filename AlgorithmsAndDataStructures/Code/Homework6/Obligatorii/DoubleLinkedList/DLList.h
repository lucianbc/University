#ifndef DLLIST_H_INCLUDED
#define DLLIST_H_INCLUDED

struct ListElement
{
    ListElement *prev;
    ListElement *next;
    int value;
};

struct DLList
{
    ListElement *first;
    ListElement *last;
    int length;
};

DLList newDLList(void);
void pushFront(DLList&, int);
void pushBack(DLList&, int);
void pushAt(DLList&, int, int);
void showForward(DLList);
void showBackward(DLList);
int deleteByValue(DLList&, int);
int deleteByIndex(DLList&, int);

#endif // DLLIST_H_INCLUDED
