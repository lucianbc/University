#include <iostream>
#include <fstream>

using namespace std;

bool G[100][100];
int n;

void citire()
{
    fstream f;
    f.open("graf.in", ios::in);
    f>>n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            f>>G[i][j];

    f.close();
}

void afisareMatrice()
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout<<G[i][j]<<" ";
        cout<<endl;
    }
}

int grad(int x)
{
    if(x < 0 || x >= n)
        return 0;

    int s = 0;

    for(int i = 0; i < n; i++)
        s += G[x][i];

    return s;
}

int NumarMuchii()
{
    int nr = 0;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++)
            nr += G[i][j];

    return nr;
}

int GradMax()
{
    int g[100] = {0};

    int max = -1;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++)
        {
            g[i] += G[i][j];
            g[j] += G[j][i];
            max = max < g[i] ? g[i] : max;
            max = max < g[j] ? g[j] : max;
        }

    for(int i = 0; i < n; i++)
        if(g[i] == max)
            cout<<i<<" ";

    cout<<endl;
    return max;
}

int main()
{
    citire();

    afisareMatrice();

    //cout<<NumarMuchii();

    GradMax();

    return 0;
}
