#include <iostream>

using namespace std;

int n, m;
char cat[2][103];
char st[103];

void processLine(char line[], int stNr)
{
    for(int i = 0; i < m; i++)
    {
        if(line[i] >= cat[0][i])
        {
            cat[0][i] = line[i];
            cat[1][i] = stNr;
        }
    }
}

void rez()
{
    cin>>n>>m;
    cin.get();
    char line[103];
    for(int i = 0; i < n; i++)
    {
        cin.getline(line, 102);
        processLine(line, i + 1);
    }

    int nr = 0;

    for(int i = 0; i < m; i++)
    {
        if(st[cat[1][i]] == 0)
        {
            nr++;
            st[cat[1][i]] = 1;
        }
    }

    cout<<nr;
}

int main()
{
    rez();
    return 0;
}
