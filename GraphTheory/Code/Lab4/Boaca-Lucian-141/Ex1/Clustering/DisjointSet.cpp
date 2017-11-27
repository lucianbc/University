//
// Created by Lucian on 04/05/2017.
//

#include "DisjointSet.h"

DisjointSet::DisjointSet(int size) : setsNr(size - 1), subseturiSz(size) {
    subseturi = new Subset[size]();
    for(int i = 0; i < size; i++) {
        subseturi[i].parinte = i;
        subseturi[i].rank = 0;
    }
}

int DisjointSet::subsetulLui(int i) {
    if(subseturi[i].parinte != i)
        subseturi[i].parinte = subsetulLui(subseturi[i].parinte);
    return subseturi[i].parinte;
}

void DisjointSet::uneste(int x, int y) {
    int parinteX = subsetulLui(x);
    int parinteY = subsetulLui(y);

    if(subseturi[parinteX].rank < subseturi[parinteY].rank)
        subseturi[parinteX].parinte = parinteY;
    else if(subseturi[parinteX].rank > subseturi[parinteY].rank)
        subseturi[parinteY].parinte = parinteX;
    else {
        subseturi[parinteY].parinte = parinteX;
        subseturi[parinteX].rank++;
    }

    setsNr--;
}

DisjointSet::~DisjointSet() {
    delete [] subseturi;
}

int DisjointSet::getSetsNr() const {
    return setsNr;
}
