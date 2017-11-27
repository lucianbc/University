//
// Created by lucian on 01-Mar-17.
//

#ifndef PROBLEME_GRAFORIENTATMATRICE_H
#define PROBLEME_GRAFORIENTATMATRICE_H


#include <iostream>

class GrafOrientatMatrice {
    int** map;
    int n, m;
public:
    GrafOrientatMatrice();

    void citire(std::istream &);

    void afisare(std::ostream &);

    ~GrafOrientatMatrice();
};


#endif //PROBLEME_GRAFORIENTATMATRICE_H
