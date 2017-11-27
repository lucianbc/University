#include <iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;
    for(int i = 0; i < 2 * n + 1; i++)
    {
        for(int j = 0; j < 2 * n + 1; j++)
        {
            int val;
            if(i <= n && j <= n) val = i + j - n;
            else if(i <= n && j > n ) val = i - (j - 1) % n - 1;
            else if(i >= n && j <= n) val = j - (i - 1) % n - 1;
            else val = 3 * n - i - j;

            if(!(val < 0 && j > n))
            {
                if(val < 0)
                    cout<<" ";
                else cout<<val;

                if(!(j >= n && val == 0))
                    cout<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}
