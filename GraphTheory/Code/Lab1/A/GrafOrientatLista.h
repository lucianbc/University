//
// Created by lucian on 01-Mar-17.
//

#ifndef PROBLEME_GRAFORIENTATLISTA_H
#define PROBLEME_GRAFORIENTATLISTA_H


#include <iostream>

class GrafOrientatLista {
    struct Nod {
        int val;
        Nod* next;
    };

    Nod** noduri;
    int m, n;

public:
    GrafOrientatLista();
    void citire(std::istream&);
    void afisare(std::ostream&);
    ~GrafOrientatLista();
};


#endif //PROBLEME_GRAFORIENTATLISTA_H
