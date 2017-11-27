#include <iostream>
#include <fstream>
#include "GrafPonderat.h"

using namespace std;

GrafPonderat citeste() {
    ifstream fin("grafpond.in") ;

    int n, m;

    fin>>n>>m;

    GrafPonderat g(n);

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

    GrafPonderat mst = graf.kruscal();

    GrafPonderat secondMst = graf.secondmst();

    cout<<"Arbore minim: ";
    mst.print();

    cout<<"Al doilea arbore minim: ";
    secondMst.print();

    return 0;
}