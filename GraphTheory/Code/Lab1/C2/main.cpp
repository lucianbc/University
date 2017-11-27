#include <iostream>
#include <fstream>

#include "DirectedGraph.h"

using namespace std;

int main() {

    ifstream fin("graf.in");

    DirectedGraph myG;
    myG.read(fin);

    myG.print(cout);

    myG.isAcyclic();

    fin.close();

    return 0;
}