#include <iostream>
#include <cstdio>

using namespace std;

int getMaxAppearing(int v[], int n)
{
    int bitMap[32] = {0};
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 32; j++)
        {
            int k = 1 << j;
            if(k & v[i])
            {
                bitMap[j]++;
            }
        }
    }

    int compMax = 0;
    for(int i = 0; i < 32; i++)
    {
        if(bitMap[i] >= n / 2 + 1)
        {
            int k = 1 << i;
            compMax = compMax | k;
        }
    }

    return compMax;
}

bool verify(int v[], int n, int c)
{
    int ct = 0;
    for(int i = 0; i < n; i++)
    {
        if(v[i] == c)
            ct++;
    }
    if(ct >= n / 2 + 1)
        return true;
    else
        return false;
}

int main()
{
    int v[] = {9, 8, 7, 6, 5, -2, -2, -2, 11, 53, -2, -2, -2, -2, -2};
    int n = sizeof(v)/sizeof(int);

    int nrM = getMaxAppearing(v, n);

    //cout<<nrM;

    if(verify(v, n, nrM))
        cout<<"Numarul majoritar din vectorul v este "<<nrM<<endl;
    else
        cout<<"Vectorul v nu contine un element majoritar"<<endl;

    return 0;
}
