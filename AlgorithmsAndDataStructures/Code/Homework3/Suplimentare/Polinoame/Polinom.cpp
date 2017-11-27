#include "Polinom.h"
#include <iostream>
#include <cstdio>

Polinom newPol()
{
    Polinom aPol;
    aPol.tail = NULL;
    aPol.head = NULL;
    aPol.length = 0;

    return aPol;
}

void pushBack(Polinom &myPol, int grad, int coef)
{
    Monom* newMon = new Monom;
    newMon->grad = grad;
    newMon->coeficient = coef;
    newMon->next = NULL;

    if(myPol.head == NULL)
    {
        myPol.head = newMon;
        myPol.tail = newMon;
    }
    else
    {
        myPol.tail->next = newMon;
        myPol.tail = newMon;
    }

    myPol.length++;
}

void pushFront(Polinom &myPol, int grad, int coef)
{
    Monom* newMon = new Monom;
    newMon->grad = grad;
    newMon->coeficient = coef;

    if(myPol.head == NULL)
    {
        newMon->next = NULL;
        myPol.head = newMon;
        myPol.tail = newMon;
    }
    else
    {
        newMon->next = myPol.head;
        myPol.head = newMon;
    }
    myPol.length++;
}

int valueAt(Polinom myPol, int poz)
{
    Monom* crt = myPol.head;

    while(poz && crt != NULL)
    {
        poz--;
        crt = crt->next;
    }
    if(crt != NULL)
    {
        return crt->grad;
    }
    else
    {
        return -1;
    }
}

void insertMonom(Polinom &myPol, int grad, int coef)
{
    if(myPol.length == 0 || valueAt(myPol, 0) > grad)
    {
        //printf("cazul %d\n", 1);
        pushFront(myPol, grad, coef);
    }
    else if(myPol.tail->grad <= grad)
    {
        pushBack(myPol, grad, coef);
        //printf("cazul %d\n", 2);
    }
    else
    {
        //printf("cazul %d\n", 3);
        Monom* crt = myPol.head;
        Monom* newMon = new Monom;
        newMon->grad = grad;
        newMon->coeficient = coef;
        while((crt->next)->grad < grad)
        {
            crt = crt->next;
        }
        newMon->next = crt->next;
        crt->next = newMon;
        myPol.length++;
    }
}

void afisarePozitionala(Monom* crt)
{
    if(crt != NULL)
    {
        afisarePozitionala(crt->next);
        printf("%dX^%d ", crt->coeficient, crt->grad);
    }
}

void showPol(Polinom myPol)
{
    afisarePozitionala(myPol.head);

    printf("\n");
}

void deletePol(Polinom& myPol)
{
    Monom* crt = myPol.head;
    while(crt != NULL)
    {
        Monom* toDel = crt;
        crt = crt->next;
        delete toDel;
        toDel->next = NULL;
    }
    myPol.head = NULL;
    myPol.tail = NULL;
}
