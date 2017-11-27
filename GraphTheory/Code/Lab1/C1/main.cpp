#include <iostream>
#include <fstream>
#include "UndirectedGraph.h"

using namespace std;

int main() {

    ifstream fin("graf.in");

    UndirectedGraph g;

    g.read(fin);

    g.print(cout);

    g.isAcyclic();

    fin.close();

    return 0;
}