#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
    int n;
    cin>>n;

    string s;
    cin>>s;

    Stack myStack = newStack();

    for(int i = 0; i < n; i++)
    {
        if(myStack.height != 0 && s[i] != peek(myStack))
        {
            pop(myStack);
        }
        else
        {
            push(myStack, s[i]);
        }
    }

    if(myStack.height == 0)
        cout<<"Numar egal de \'a\'uri si \'b\'uri\n";
    else
        cout<<"Numar inegal\n";

    return 0;
}
