#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
    const char *c = "asdfghjkl";
    c[3] = 'q';
    cout<<c;
}
