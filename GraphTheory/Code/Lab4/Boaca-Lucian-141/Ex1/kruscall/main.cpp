#include <iostream>
#include <fstream>
#include "GrafPonderat.h"

using namespace std;

GrafPonderat citeste() {
    ifstream fin("grafpond.in") ;

    GrafPonderat g;

    int n, m;

    fin>>n>>m;

    g.setN(n);
    g.setM(m);

    for(int i = 0; i < m; i++) {
        int u, v, w;
        fin>>u>>v>>w;
        g.adaugaMuchie(u, v, w);
    }

    return g;
}

int main() {

    GrafPonderat graf = citeste();

//    graf.print();

    GrafPonderat mst = graf.kruscal();

    mst.print();


    return 0;
}