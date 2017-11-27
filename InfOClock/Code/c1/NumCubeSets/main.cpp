//https://csacademy.com/contest/round-13/#task/num-cube-sets
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

using namespace std;

typedef unsigned long long int i64;

int mx = 500;

void showProd()
{
    i64 cprd = 1;
    vector<bool> primes(mx, true);
    for(int p = 2; p <= mx; p++)
    {
        if(primes[p] == false)
            continue;

        cprd*=p;
        cout<<p<<": "<<cprd<<endl;

        for(int i = p + p; i <= mx; i += p)
            primes[i] = false;
    }
    cout<<endl<<endl<<cprd<<endl;
}

int main()
{
    cout<<pow(10, 5)<<endl;
    cout<<USHRT_MAX;
    //showProd();
}
