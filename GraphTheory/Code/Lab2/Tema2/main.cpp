#include <iostream>
#include <fstream>
#include "Graf.h"

using namespace std;

int main() {

    ifstream fin("graf.in");

    Graf g;
    fin>>g;
//    cout<<g;

//    g.GetArticulationPoints();

    g.GetCriticalEdges();

    fin.close();

    return 0;
}