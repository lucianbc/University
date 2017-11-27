#include <iostream>
#include <string>

using namespace std;

// Complexitate timp O(n)
// Complexitate spatiu O(1)

// baababbaabaab
int getBorderLength(string s)
{
    int borders[s.size()];
    borders[0] = 0;
    for(int i = 1; i < s.size(); i++)
    {
        int lastBorder = borders[i - 1];
        while(lastBorder > 0 && s[i] != s[lastBorder])
        {
            lastBorder = borders[lastBorder - 1];
        }
        if(s[i] == s[lastBorder])
            borders[i] = lastBorder + 1;
        else
            borders[i] = 0;
    }

    return borders[s.size() - 1];
}

int main()
{
    string s;
    cin>>s;

    int lg = getBorderLength(s);

    // Afisare margine
    if(lg > 0)
    {
        for(int i = 0; i < lg; i++)
            cout<<s[i];
        cout<<endl;
    }
    else
        cout<<"Sirul introdus nu are margine.\n";

    return 0;
}
