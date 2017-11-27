#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

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
// Exercitiul 4:
// Scrieţi un program în care se citesc două numere “mari” şi se construieşte o listă
// în care se va salva suma lor.
List numberToList(char nr[])
{
    List number = newList();

    for(int i = 0; i < strlen(nr); i++)
    {
        int n = nr[i] - 48;
        pushFront(number, n);
    }

    return number;
}

void listToNumber(List listNumber, char nr[])
{
    int i = 0;

    Node* crt = listNumber.head;

    while(crt != NULL)
    {
        nr[i] = crt->value + 48;
        i++;
        crt = crt->next;
    }
    nr[i] = '\0';
    reverse(nr, nr + strlen(nr));
}

List sumTwoLists(List number1, List number2)
{
    List sum = newList();
    int reminder = 0;

    Node* nr1 = number1.head;
    Node* nr2 = number2.head;

    while(nr1 != NULL || nr2 != NULL)
    {
        int c1 = nr1 == NULL ? 0 : nr1->value;
        int c2 = nr2 == NULL ? 0 : nr2->value;

        if(nr1) nr1 = nr1->next;
        if(nr2) nr2 = nr2->next;

        int cs = c1 + c2 + reminder;

        pushBack(sum, cs%10);
        reminder = cs/10;
    }

    if(reminder != 0)
        pushBack(sum, reminder);

    return sum;
}

void exercitiul4()
{
    char nr1[256], nr2[256];

    printf("Introduceti numerele pe care doriti sa le adunati:\n");

    scanf("%s", nr1);
    scanf("%s", nr2);

    if(strlen(nr1) < strlen(nr2))
    {
        char temp[255];
        strcpy(temp, nr1);
        strcpy(nr1, nr2);
        strcpy(nr2, temp);
    }

    List numar1 = numberToList(nr1);
    List numar2 = numberToList(nr2);

    List suma = sumTwoLists(numar1, numar2);

    char rez[256];
    listToNumber(suma, rez);

    printf("Suma celor doua numere este: %s.\n");
}


int main()
{
    exercitiul4();

    return 0;
}
