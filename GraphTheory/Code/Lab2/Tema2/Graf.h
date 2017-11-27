//
// Created by lucian on 19-Mar-17.
//

#ifndef TEMA2_GRAF_H
#define TEMA2_GRAF_H

#include <list>
#include <vector>
#include <iostream>

using namespace std;

struct Nod {
    list<int> vecini;
};

struct Muchie {
    int u, v;

    Muchie(int u, int v) : u(u), v(v) { }
};

class Graf {
    vector<Nod> noduri;
    int n, m;

    friend istream&operator>>(istream& in, Graf& g);
    friend ostream&operator<<(ostream& out, Graf& g);

    void df(int i, bool *checked, int *t, int *nv, int *L, int *c, int start, int& grad_start);
    void df_muchii(int i, bool *checked, int *t, int *nv, int *L, vector<Muchie> &muchii);

public:
    void GetArticulationPoints();
    void GetCriticalEdges();
};


#endif //TEMA2_GRAF_H
