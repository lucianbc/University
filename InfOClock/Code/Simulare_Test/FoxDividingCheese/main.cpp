#include <iostream>

using namespace std;

int getPow(int &a, int d)
{
    int p = 0;
    while(a % d == 0)
    {
        a = a / d;
        p++;
    }
    return p;
}

int cmmdc(int m, int n)
{
    if(n == 0)
    {
        return m;
    }
    return cmmdc(n, m % n);
}

int main()
{
    int a, b;

    cin>>a>>b;

    int pow2a = getPow(a, 2);
    int pow2b = getPow(b, 2);
    int pow3a = getPow(a, 3);
    int pow3b = getPow(b, 3);
    int pow5a = getPow(a, 5);
    int pow5b = getPow(b, 5);

    if(a == b)
        cout<<abs(pow2a - pow2b) + abs(pow3a - pow3b) + abs(pow5a - pow5b);
    else cout<<-1;

    return 0;
}
