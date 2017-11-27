//
// Created by Lucian on 04/05/2017.
//

#ifndef EX1_DISJOINTSET_H
#define EX1_DISJOINTSET_H

struct Subset {
    int parinte;
    int rank;
};

class DisjointSet {
private:
    Subset * subseturi;

public:
    DisjointSet(int size);

    int subsetulLui(int i);

    void uneste(int x, int y);

    virtual ~DisjointSet();

};


#endif //EX1_DISJOINTSET_H
