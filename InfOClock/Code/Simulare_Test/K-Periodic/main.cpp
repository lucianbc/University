#include <iostream>

using namespace std;

int main()
{
    int n, k;
    cin>>n>>k;

    int ar[n];

    for(int i = 0; i < n; i++)
        cin>>ar[i];

    int ct = 0;

    for(int p = 0; p < k; p++)
    {
        int vals_to_change = 0;
        for(int b = 0; b < n / k; b++)
        {
            vals_to_change += ar[p + b * k] - 1;
        }

        ct = ct + min(vals_to_change, n / k - vals_to_change);
    }

    cout<<ct<<endl;

    return 0;
}
