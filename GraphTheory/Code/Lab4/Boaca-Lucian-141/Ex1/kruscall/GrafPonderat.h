//
// Created by Lucian on 04/05/2017.
//

#ifndef EX1_GRAFPONDERAT_H
#define EX1_GRAFPONDERAT_H

#include <queue>
#include <vector>
#include <sstream>
#include <iostream>
#include "DisjointSet.h"

using namespace std;

struct Muchie {
    int c1, c2, pondere;

    Muchie(int c1, int c2, int pondere);

    string toString() const;
};

struct Comparator {
    bool operator()(Muchie m1, Muchie m2);
};

class GrafPonderat {

    typedef priority_queue<Muchie, vector<Muchie>, Comparator> minHeapMuchii;

private:
    minHeapMuchii muchii;
    int N, M;

public:
    void adaugaMuchie(int c1, int c2, int pondere);

    int getN() const;

    void setN(int N);

    int getM() const;

    void setM(int M);

    void print() {
        cout<<N<<" "<<M<<endl;
        minHeapMuchii muchiilocal = muchii;

        while(muchiilocal.size()) {
            cout<<muchiilocal.top().toString()<<endl;
            muchiilocal.pop();
        }
    }

    GrafPonderat kruscal() {
        GrafPonderat mst;
        mst.N = this->N;
        mst.M = mst.N - 1; // N - 1 muchii
        DisjointSet disjointSet(N + 1);
        minHeapMuchii muchiiCopy = muchii;

        while(mst.muchii.size() < N - 1) {
            Muchie crtM = muchiiCopy.top();
            muchiiCopy.pop();
            int c1Set = disjointSet.subsetulLui(crtM.c1);
            int c2Set = disjointSet.subsetulLui(crtM.c2);
            if(c1Set != c2Set) {
                mst.adaugaMuchie(crtM.c1, crtM.c2, crtM.pondere);
                disjointSet.uneste(crtM.c1, crtM.c2);
            }
        }
        return mst;
    }

};


#endif //EX1_GRAFPONDERAT_H
