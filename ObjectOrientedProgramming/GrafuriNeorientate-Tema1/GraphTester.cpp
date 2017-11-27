//
// Created by lucian on 18-Mar-17.
//

#include <fstream>
#include "GraphTester.h"
#include "Graph.h"

void GraphTester::test() {
    fstream fin("graf.in");
    fstream fin2("graf2.in");

    Graph g1;
    fin>>g1;

    cout<<"Afisare Graf1:\n";
    cout<<g1<<endl;

    Graph g2;
    fin2>>g2;

    cout<<"Afisare Graf2:\n";
    cout<<g2<<endl;

    Graph g3;
    g3 = g1 + g2;

    cout<<"Afisare Graf3, suma Graf1 + Graf2:\n";
    cout<<"muchii / varfuri: "<<g3.getEdgesNumber()<<" "<<g3.getVerticesNumber()<<endl;
    cout<<g3<<endl;

    LinkedList<LinkedList<int> *> *paths = g3.GedPathsList();

    cout<<"Afisare drumuri in graful G3: \n";
    for(LinkedList<int> * lptr : *paths) {
        for(int i : *lptr) {
            cout<<i<<" ";
        }
        cout<<endl;
    }

    // Dezalocarea rezultatului anterior
    for(LinkedList<int> * lptr : *paths) {
        delete(lptr);
    }
    delete(paths);

    cout<<"Parcurgere in lungime a grafului G1:\n";

    LinkedList<int> *bfs = g1.BreadthFirstTraversal();
    for(int nod : *bfs) {
        cout<<nod<<" ";
    }
    cout<<endl;
    delete bfs;

    cout<<"Parcurgere in latime a grafului G2:\n";

    LinkedList<int> *dfs = g2.DepthFirstTraversal();
    for(int nod : *dfs) {
        cout<<nod<<" ";
    }
    cout<<endl;
    delete dfs;

    fin2.close();
    fin.close();
}
