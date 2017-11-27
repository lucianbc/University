#include <iostream>
#include <fstream>
#include "Automaton.h"

using namespace std;

int main() {

    Automaton automat;

    ifstream fin("automat4.in");

    automat.citeste(fin);

    fin.close();

    //automat.afisare(cout);

    cout<<automat.evaluate("aaa")<<endl;
    cout<<automat.evaluate("abaaab")<<endl;
    cout<<automat.evaluate("ba")<<endl;
    cout<<automat.evaluate("ca")<<endl;
    cout<<automat.evaluate("")<<endl;

    return 0;

}