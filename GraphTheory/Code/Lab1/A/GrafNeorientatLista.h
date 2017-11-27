#ifndef PROBLEME_GRAFNEORIENTATLISTA_H
#define PROBLEME_GRAFNEORIENTATLISTA_H

#include <vector>
#include <iostream>
#include <fstream>

namespace GrafNeorientatLista
{
    struct Nod
    {
        int val;
        Nod* next;
    };

    std::vector<Nod*>* citeste(std::istream&);
    void afisare(std::vector<Nod*>*, std::ostream&);
    void dezalocare(std::vector<Nod*> *&);
}

#endif //PROBLEME_GRAFNEORIENTATLISTA_H
