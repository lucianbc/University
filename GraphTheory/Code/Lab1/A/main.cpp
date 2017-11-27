#include <iostream>
#include <fstream>
#include "GrafNeorientatMatrice.h"
#include "GrafNeorientatLista.h"

#include "GrafOrientatMatrice.h"
#include "GrafOrientatLista.h"

using namespace std;
//using namespace GrafNeorientatLista;

//void testGrafNeorientatMatrice()
//{
//    ifstream fin("graf.in");
//
//    vector<vector<int>> G = citeste(fin);
//
//    fin.close();
//
//    afisare(G, cout);
//}

//void testGrafNeorientatLista()
//{
//    ifstream fin("graf.in");
//
//    vector<Nod*> *G = citeste(fin);
//
//    fin.close();
//
//    afisare(G, cout);
//
//    dezalocare(G);
//}

void grafOrientatMatriceTest() {
    GrafOrientatMatrice myGraf;

    ifstream fin("graf.in");

    myGraf.citire(fin);

    myGraf.afisare(cout);
}

void grafOrientatListaTest() {
    GrafOrientatLista myG;

    ifstream fin("graf.in");

    myG.citire(fin);

    fin.close();

    myG.afisare(cout);
}

int main() {
    grafOrientatListaTest();
    return 0;
}