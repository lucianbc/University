#include <iostream>
#include <cmath>

using namespace std;

int Stirling(int n, int m)
{
    if(n == m || m == 1)
        return 1;
    return Stirling(n - 1, m - 1) + m * Stirling(n, m - 1);
}

int main()
{
    int m, n; // fct def pe {1, 2,.., n} -> {1, 2,..., m}, m <= n
    cin>>n>>m;
    int fct = Stirling(n, m);

    cout<<fct;

    return 0;
}
