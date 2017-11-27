#include <iostream>
#include <cstdlib>
using namespace std;

struct KeyValue
{
    unsigned short int key;
    int value;
};

int cresc(const void *a, const void *b)
{
    return ((KeyValue*)a)->value - ((KeyValue*)b)->value;
}

int desc(const void *a, const void *b)
{
    return ((KeyValue*)b)->value - ((KeyValue*)a)->value;
}

int main()
{
    unsigned short int t;
    unsigned short int n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        KeyValue a[n], b[n];
        int sol[n+1];
        for(int i = 0; i < n; i++)
        {
            cin>>a[i].value;
            a[i].key = i + 1;
        }
        for(int i = 0; i < n; i++)
        {
            cin>>b[i].value;
            b[i].key = i + 1;
        }

        qsort(a, n, sizeof(KeyValue), cresc);
        qsort(b, n, sizeof(KeyValue), desc);

        bool ok = true;

        for(int i = 0; i < n; i++)
            cout<<"("<<a[i].value<<","<<a[i].key<<"), ";
        cout<<endl;

        for(int i = 0; i < n; i++)
            cout<<"("<<b[i].value<<","<<b[i].key<<"), ";
        cout<<endl;

        for(int i = 1; i <= n; i++)
        {
            sol[a[i-1].key] = b[i-1].key;
        }

        if(ok)
        {
            for(int i = 1; i <= n; i++)
                cout<<sol[i]<<" ";
        }
        else
            cout<<-1<<endl;
    }
    return 0;
}
