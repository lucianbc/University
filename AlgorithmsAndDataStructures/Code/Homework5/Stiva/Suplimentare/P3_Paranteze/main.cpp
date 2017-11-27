#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

int main()
{
    Stack myStack = newStack();

    string paranteze;
    cin>>paranteze;

    bool isOk = true;

    for(int i = 0; i < paranteze.size(); i++)
    {
        if(paranteze[i] == '(')
            push(myStack, i);
        else
        {
            if(myStack.height == 0)
            {
                cout<<i<<endl;
                isOk = false;
                break;
            }
            else
                pop(myStack);
        }
    }

    if(isOk && myStack.height == 0) cout<<"Configuratie corecta!\n";
    else
    {
        int crt;
        while(myStack.height != 0)
        {
            crt = pop(myStack);
        }
        cout<<crt;
    }

    return 0;
}
