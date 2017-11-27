#include "GrafNeorientatMatrice.h"
#include <iostream>
#include <fstream>

using namespace std;

vector<vector<int>> GrafNeorientatMatrice::citeste(istream &fin)
{
    unsigned int n, m;
    fin>>n>>m;

    vector<vector<int>> G(n, vector<int>(n, 0));

    for(int i = 0; i < m; i++)
    {
        int x, y;
        fin>>x>>y;
        G[--x][--y]++;
        G[y][x]++;
    }

    return G;
}

void GrafNeorientatMatrice::afisare(std::vector<std::vector<int>> G, ostream &out)
{
    for(int i = 0; i < G.size(); i++)
    {
        for(int j = 0; j < G[i].size(); j++)
            out<<G[i][j]<<" ";
        out<<endl;
    }
}