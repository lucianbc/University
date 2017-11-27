#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
    Stack stiva = newStack();
    push(stiva, 1);
    push(stiva, 2);
    push(stiva, 3);

    afiseaza(stiva);

    pop(stiva);
    pop(stiva);
    pop(stiva);
    pop(stiva);

    return 0;
}
