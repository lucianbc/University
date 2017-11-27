#include <iostream>
#include "Queue.h"

using namespace std;

int main()
{
    Queue myQ = newQueue();

    push(92, myQ);
    push(93, myQ);
    push(12, myQ);

    afiseaza(myQ);
    cout<<endl;

    pop(myQ);
    pop(myQ);
    pop(myQ);
    pop(myQ);

    return 0;
}
