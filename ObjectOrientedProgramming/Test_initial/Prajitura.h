//
// Created by lucian on 02-Mar-17.
//

#ifndef TEST_INITIAL_PRAJITURA_H
#define TEST_INITIAL_PRAJITURA_H

#include <vector>
#include "Forme.h"
#include <iostream>

class Prajitura {

    std::vector<Forma*> prajituri;

    void add(std::string tip, std::istream& in, std::ostream& out);
    void remove(int x);
    void afiseazaTotal(std::ostream& out);

public:
    void run(std::istream& in, std::ostream& out);

    virtual ~Prajitura();
};


#endif //TEST_INITIAL_PRAJITURA_H
