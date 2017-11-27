//
// Created by Lucian on 05/05/2017.
//

#ifndef SECONDMST_DISJOINTSET_H
#define SECONDMST_DISJOINTSET_H


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



#endif //SECONDMST_DISJOINTSET_H
