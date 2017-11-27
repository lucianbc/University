#include <iostream>
#include <cmath>

#include "Polinom.h"

using namespace std;

Polinom citestePolinom()
{
    int n;
    cout<<"Introduceti numarul de monoame:\n";
    cin>>n;

    Polinom p = newPol();

    for(int i = 1; i <= n; i++)
    {
        cout<<"Introduceti coeficientul si gradul monomului curent: ";
        int g, c;
        cin>>c>>g;
        cout<<endl;
        insertMonom(p, g, c);
    }

    return p;
}

void inmultirePolinomScalar(Polinom& pol, int s)
{
    Monom* crt = pol.head;
    while(crt != NULL)
    {
        crt->coeficient *= s;
        crt = crt->next;
    }
}

void ex_2()
{
    Polinom p = citestePolinom();
    int sc;
    cout<<"Introduceti valoarea scalarului intreg: "; cin>>sc;
    inmultirePolinomScalar(p, sc);
    showPol(p);
}

int evalPol(Polinom p, int x)
{
    int s = 0;

    Monom* crt = p.head;

    while(crt != NULL)
    {
        s += crt->coeficient * pow(x, crt->grad);
        crt = crt->next;
    }

    return s;
}

void ex_3()
{
    Polinom p = citestePolinom();
    int x0;
    showPol(p);
    cout<<"x0 = "; cin>>x0;
    int val = evalPol(p, x0);
    cout<<"Valoarea polinomului in x0 este "<<val;
}

Polinom sumaPolinoame(Polinom p, Polinom q)
{
    Polinom suma = newPol();
    Monom* ip = p.head;
    Monom* iq = q.head;

    while(ip != NULL && iq != NULL)
    {
        int newGrad, newCof;
        if(ip->grad == iq->grad)
        {
            newGrad = ip->grad;
            newCof = ip->coeficient + iq->coeficient;
            ip = ip->next;
            iq = iq->next;
        }
        else if(ip->grad < iq->grad)
        {
            newGrad = ip->grad;
            newCof = ip->coeficient;
            ip = ip->next;
        }
        else
        {
            newGrad = iq->grad;
            newCof = iq->coeficient;
            iq = iq->next;
        }
        insertMonom(suma, newGrad, newCof);
    }

    //cout<<"ajuns\n";

    Monom* ir = ip == NULL ? iq : ip;
    while(ir != NULL)
    {
        insertMonom(suma, ir->grad, ir->coeficient);
        ir = ir->next;
    }

//    if(ip == NULL)
//    {
//        while(iq != NULL)
//        {
//            insertMonom(suma, iq->grad, iq->coeficient);
//            iq = iq->next;
//        }
//    }
//    else if(iq == NULL)
//    {
//        while(ip != NULL)
//        {
//            insertMonom(suma, iq->grad, iq->coeficient);
//            iq = iq->next;
//        }
//    }
    return suma;
}

void ex_4()
{
    cout<<"Introduceti primul polinom:\n";
    Polinom p = citestePolinom();
    cout<<"Introduceti al doilea polinom polinom:\n";
    Polinom q = citestePolinom();

    cout<<"P: "; showPol(p);

    cout<<"Q: "; showPol(q);

    Polinom s = sumaPolinoame(p, q);

    cout<<"S: "; showPol(s);
}

Polinom produsPolinoame(Polinom p, Polinom q)
{
    Polinom sumaPartiale = newPol();

    Monom* ip = p.head;

    while(ip != NULL)
    {
        Polinom produs = newPol();
        Monom* iq = q.head;
        while(iq != NULL)
        {
            int newGrad = (iq->grad) + (ip->grad);
            int newCf = iq->coeficient * ip->coeficient;
            insertMonom(produs, newGrad, newCf);
            iq = iq->next;
        }

        sumaPartiale = sumaPolinoame(sumaPartiale, produs);

        ip = ip->next;
    }

    return sumaPartiale;
}

void ex_5()
{
    cout<<"Introduceti primul polinom:\n";
    Polinom p = citestePolinom();
    cout<<"Introduceti al doilea polinom polinom:\n";
    Polinom q = citestePolinom();

//    Polinom p = newPol();
//    Polinom q = newPol();
//
//    insertMonom(p, 3, 2);
//    insertMonom(p, 2, 2);
//    insertMonom(p, 1, 5);
//    insertMonom(p, 0, 3);
//
//    insertMonom(q, 2, 3);
//    insertMonom(q, 1, 3);
//    insertMonom(q, 0, 5);

    cout<<"P: "; showPol(p);

    cout<<"Q: "; showPol(q);

    Polinom r = produsPolinoame(p, q);

    cout<<"R: "; showPol(r);
}

int main()
{
    ex_5();

    return 0;
}
