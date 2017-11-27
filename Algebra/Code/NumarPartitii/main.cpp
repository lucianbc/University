// Acest program numara modurile in care un numar n poate fi impartit in
// sume de forma k1 + k2 + ... + km = n, unde k1 <= k2 <= k3 <= .. <= km <= n

#include <vector>
#include <stack>
#include <iostream>

using namespace std;

unsigned long long int numarPartitii(unsigned long long int n)
{
    if(n == 0 || n == 1)
        return 1;

    vector<unsigned long long int> cofs(n+1, 0);

    cofs[0] = 1;

    for(int i = 1; i <= n; i++)
    {
        for(int q = 0; q <= n - i; q++)
            cofs[q + i] = cofs[q + i] + cofs[q];
    }

    return cofs[n];
}

// aceasta este o functie ajutatoare care afiseza un numar
// cu spatii despartitoare, pentru a fi mai usor de citit
void afiseazaNumarFormatat(unsigned long long int x)
{
    stack<char> formattedNumber;

    int ct = 0;

    while(x > 0)
    {
        ct++;
        formattedNumber.push((char)(x%10 + 48));
        x/=10;

        if(ct % 3 == 0 && x != 0)
            formattedNumber.push('.');

    }

    while(!formattedNumber.empty())
    {
        cout<<formattedNumber.top();
        formattedNumber.pop();
    }
}

int main()
{
    int n;
    cin>>n;
    afiseazaNumarFormatat(numarPartitii(n));

    return 0;
}
