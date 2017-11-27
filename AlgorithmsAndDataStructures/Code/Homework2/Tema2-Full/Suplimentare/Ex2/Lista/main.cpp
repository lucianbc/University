// Lista 2.0
#include <iostream>
#include <cstdio>

using namespace std;

// Obligatorii

struct Node {
    int value;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
    int length;
};

List newList()
{
    List aList;
    aList.tail = NULL;
    aList.head = NULL;
    aList.length = 0;

    return aList;
}

void pushBack(List &myList, int val)
{
    Node* newNode = new Node;
    newNode->value = val;
    newNode->next = NULL;

    if(myList.head == NULL)
    {
        myList.head = newNode;
        myList.tail = newNode;
    }
    else
    {
        myList.tail->next = newNode;
        myList.tail = newNode;
    }

    myList.length++;
}

void pushFront(List &myList, int val)
{
    Node* newNode = new Node;
    newNode->value = val;

    if(myList.head == NULL)
    {
        newNode->next = NULL;
        myList.head = newNode;
        myList.tail = newNode;
    }
    else
    {
        newNode->next = myList.head;
        myList.head = newNode;
    }
    myList.length++;
}

void insertAt(List &myList, int val, int poz)
{
    if(poz == 0)
    {
        pushFront(myList, val);
    }
    else
    {
        Node* crt = myList.head;
        poz--;
        while(poz >= 1 && crt != NULL)
        {
            poz--;
            crt = crt->next;
        }
        if(crt != NULL)
        {
            Node* newNode = new Node;
            newNode->value = val;
            newNode->next = crt->next;
            crt->next = newNode;
            myList.length++;
            if(newNode->next == NULL)
                myList.tail = newNode;
        }
        else
        {
            printf("Pozitia nu exista!\n");
        }
    }
}

void insertBefore(List &myList, int val, int mark)
{
    if(myList.head != NULL)
    {
        if(myList.head->value == mark)
        {
            pushFront(myList, val);
        }
        else
        {
            Node* crt = myList.head;

            while(crt->next != NULL && (crt->next)->value != mark && (crt->next)->next != NULL)
            {
                crt = crt->next;
            }
            if(crt->next != NULL && (crt->next)->value == mark)
            {
                Node* newNode = new Node;
                newNode->value = val;
                newNode->next = crt->next;
                crt->next = newNode;
                myList.length++;
            }
            else
            {
                printf("Elementul inaintea caruia doriti sa inserati valoarea nu exista!\n");
            }
        }
    }
    else
    {
        printf("Lista nu contine niciun element!\n");
    }
}

void insertAfter(List &myList, int val, int mark)
{
    Node* crt = myList.head;

    while(crt != NULL && crt->value != mark)
        crt = crt->next;

    if(crt != NULL)
    {
        Node* newNode = new Node;
        newNode->value = val;
        newNode->next = crt->next;
        crt->next = newNode;
        myList.length++;
        if(newNode->next == NULL)
            myList.tail = newNode;
    }
    else
    {
        printf("Elementul dupa care doriti sa inserati valoarea nu a fost gasit!\n");
    }
}

void showList(List myList)
{
    Node* crt = myList.head;
    while(crt != NULL)
    {
        printf("%d ", crt->value);
        crt = crt->next;
    }
    printf("\n");
}

int findByValue(List myList, int val)
{
    Node* crt = myList.head;
    int poz = 0;
    while(crt != NULL)
    {
        if(crt->value == val)
            return poz;
        crt = crt->next;
        poz++;
    }
    return -1;
}

int valueAt(List myList, int poz)
{
    Node* crt = myList.head;

    while(poz && crt != NULL)
    {
        poz--;
        crt = crt->next;
    }
    if(crt != NULL)
    {
        return crt->value;
    }
    else
    {
        return -1;
    }
}

int deleteAt(List& myList, int poz)
{
    Node* crt = myList.head;

    if(crt != NULL)
    {
        if(poz == 0)
        {
            if(myList.head == myList.tail)
            {
                //lista contine un singur element
                myList.head = NULL;
                myList.tail = NULL;
                int valToReturn = crt->value;
                delete crt;
                return valToReturn;
            }
            else
            {
                myList.head = myList.head->next;
                int valToReturn = crt->value;
                delete crt;
                return valToReturn;
            }
        }
        else
        {
            poz--;
            while(poz >= 1 && crt != NULL)
            {
                crt = crt->next;
                poz--;
            }
            if(crt->next != NULL)
            {
                Node* nextAddress = (crt->next)->next;
                if(nextAddress == NULL)
                {
                    cout<<"Sterg ultimul"<<endl;
                    myList.tail = crt;
                }
                int valToRet = (crt->next)->value;
                delete crt->next;
                crt->next = nextAddress;
                return valToRet;
            }
        }
    }
    else
    {
        printf("Lista nu contine niciun element!\n");
        return -1;
    }
    return -1;
}

int deleteByValue(List& myList, int valToDelete)
{
    if(myList.head != NULL)
    {
        int poz = 0;
        Node* crt = myList.head;
        if(crt->value == valToDelete)
        {
            if(myList.head == myList.tail)
            {
                myList.head = NULL;
                myList.tail = NULL;
                delete crt;
                return poz;
            }
            else
            {
                myList.head = myList.head->next;
                delete crt;
                return poz;
            }
        }
        else
        {
            Node* prev = NULL;
            while(crt != NULL && crt->value != valToDelete)
            {
                prev = crt;
                crt = crt->next;
                poz++;
            }
            if(crt != NULL)
            {
                Node* toDel = crt;
                if(crt->next == NULL)
                {
                    myList.tail = prev;
                }
                prev->next = crt->next;
                crt = crt->next;
                delete toDel;
                return poz;
            }
            else
            {
                return -1;
            }
        }
    }
    else
    {
        printf("Lista nu contine elemente!\n");
        return -1;
    }
}

void deleteList(List& myList)
{
    Node* crt = myList.head;
    while(crt != NULL)
    {
        Node* toDel = crt;
        crt = crt->next;
        delete toDel;
        toDel->next = NULL;
    }
    myList.head = NULL;
    myList.tail = NULL;
}

// End Obligatorii

// Suplimentare
// Exercitiul 2:
// Să se creeze o listă simplu înlănţuită alocată dinamic în care se vor reţine
// numere întregi. Să se scrie un program pentru numărarea elementelor pare din listă şi
// pentru calcularea mediei aritmetice a celor impare
void rezolvare_ex2(List myList);

void exercitiul2()
{
    List lista = newList();
    pushBack(lista, 2);
    pushBack(lista, 45);
    pushBack(lista, 547);
    pushBack(lista, 124);
    pushBack(lista, 8);
    pushBack(lista, 97);
    pushBack(lista, 125);
    pushBack(lista, 115);
    pushBack(lista, 93);
    pushBack(lista, -2);

    rezolvare_ex2(lista);
}

void rezolvare_ex2(List myList)
{
    int nrPare = 0, nrImp = 0, sumImp = 0;

    Node* crt = myList.head;

    while(crt != NULL)
    {
        if(crt->value % 2 == 0)
            nrPare++;
        else
        {
            nrImp++;
            sumImp += crt->value;
        }

        crt = crt->next;
    }

    float media = (float)sumImp/nrImp;
    printf("In lista se gasesc %d numere pare,\n%d numere impare,\niar media artmetica a acestora este %.2f.\n", nrPare, nrImp, media);
}

int main()
{
    exercitiul2();

    return 0;
}
