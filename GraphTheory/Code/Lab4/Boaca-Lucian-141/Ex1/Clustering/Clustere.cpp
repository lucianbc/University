//
// Created by Lucian on 04/05/2017.
//

#include "Clustere.h"

#include <cstring>

Muchie::Muchie(int c1, int c2, int pondere) : c1(c1), c2(c2), pondere(pondere) {}

string Muchie::toString() const {
    stringstream converter;
    converter<<c1<<" "<<c2<<" "<<pondere;
    return converter.str();
}

bool Comparator::operator()(Muchie m1, Muchie m2) {
    return m1.pondere > m2.pondere;
}

void GrafPonderat::adaugaMuchie(int c1, int c2, int pondere) {
    this->muchii.push(Muchie(c1, c2, pondere));
    this->M++;
}

int GrafPonderat::getN() const {
    return N;
}

void GrafPonderat::setN(int N) {
    GrafPonderat::N = N;
}

int GrafPonderat::getM() const {
    return M;
}

void GrafPonderat::setM(int M) {
    GrafPonderat::M = M;
}

