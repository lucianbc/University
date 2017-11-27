#include <iostream>
#include "Stack.h"

#define NPINIMAX 100

using namespace std;

int main()
{
    Stack pini = newStack();

    int n;
    //int pereche[NPINIMAX];

    cin>>n;

    for(int i = 0; i < n; i++)
    {
        int cPin;
        cin>>cPin;
        if(pini.height != 0 && peek(pini) == cPin)
            pop(pini);
        else
            push(pini, cPin);
    }

    if(empty(pini))
        cout<<"Configuratie valida.\n";
    else
        cout<<"Configuratie invalida.\n";

    return 0;
}
