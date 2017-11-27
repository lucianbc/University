#include <iostream>
#include "Lista.h"

using namespace std;

List vectorToList(int v[], int n)
{
    List rVect = newList();
    rVect.vectorLength = n;
    for(int i = 0; i < n; i++)
    {
        if(v[i] != 0)
            pushBack(rVect, v[i], i);
    }
    return rVect;
}

void printVector(List myVector)
{
    int lastIndex = 0;
    Node* crt = myVector.head;
    while(crt != NULL)
    {
        while(lastIndex < crt->index)
        {
            printf("0 ");
            lastIndex++;
        }
        lastIndex++;
        printf("%d ", crt->value);
        crt = crt->next;
    }

    while(lastIndex < myVector.vectorLength)
    {
        printf("0 ");
        lastIndex++;
    }
    printf("\n");
}

List suma(List a, List b)
{
    Node* ca = a.head;
    Node* cb = b.head;
    List s = newList();
    s.vectorLength = a.vectorLength > b.vectorLength ? a.vectorLength : b.vectorLength;
    while(ca != NULL && cb != NULL)
    {
        if(ca->index == cb->index)
        {
            pushBack(s, ca->value + cb->value, ca->index);
            ca = ca->next;
            cb = cb->next;
        }
        else if(ca->index < cb->index)
        {
            pushBack(s, ca->value, ca->index);
            ca = ca->next;
        }
        else
        {
            pushBack(s, cb->value, cb->index);
            cb = cb->next;
        }
    }
    Node* rem = ca == NULL ? cb : ca;
    while(rem != NULL)
    {
        pushBack(s, rem->value, rem->index);
        rem = rem->next;
    }
    return s;
}

int produs(List a, List b)
{
    Node* ca = a.head;
    Node* cb = b.head;

    int sum = 0;

    while(ca != NULL && cb != NULL)
    {
        if(ca->index == cb->index)
        {
            sum+= ca->value * cb->value;
            ca = ca->next;
            cb = cb->next;
        }
        else if(ca->index < cb->index)
        {
            ca = ca->next;
        }
        else
        {
            cb = cb->next;
        }
    }

    return sum;
}

void test()
{
    int v[] = {0, 0, 5, 3, 6, 12, 532, 12, 0, 5, 0, 0};

    List myVector = newList();

    myVector = vectorToList(v, sizeof(v)/sizeof(v[0]));

    showList(myVector);

    printVector(myVector);
}

int main()
{
    //int v1[] = {0, 0, 5, 0, 3, 19, 20, 11, 0, 0, 0, 19, 0};
    //int v2[] = {1, 0, 19, 0, 0, 0, 11, 6, 0};
    //int n1 = sizeof(v1)/sizeof(v1[0]);
    //int n2 = sizeof(v2)/sizeof(v2[0]);

    //List sum = suma(vectorToList(v1, n1), vectorToList(v2, n2));
    //printVector(sum);

    int v1[] = {0, 0, 0, 0, 0, 1, 2, 0, 3};
    int v2[] = {0, 0, 0, 1, 0, 2, 0, 0, 3};
    int n1 = sizeof(v1)/sizeof(v1[0]);
    int n2 = sizeof(v2)/sizeof(v2[0]);

    cout<<"suma: "<<endl;
    List sum = suma(vectorToList(v1, n1), vectorToList(v2, n2));
    printVector(sum);


    cout<<"produs: ";
    int prod = produs(vectorToList(v1, n1), vectorToList(v2, n2));
    cout<<prod<<endl;

    return 0;
}
