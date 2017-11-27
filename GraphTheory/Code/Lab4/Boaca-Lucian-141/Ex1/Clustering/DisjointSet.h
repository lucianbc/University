//
// Created by Lucian on 04/05/2017.
//

#ifndef CLUSTERING_DISJOINTSET_H
#define CLUSTERING_DISJOINTSET_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Subset {
    int parinte;
    int rank;
};

class DisjointSet {
private:
    Subset * subseturi;
    int subseturiSz;
    int setsNr;

public:
    DisjointSet(int size);

    int subsetulLui(int i);

    void uneste(int x, int y);

    virtual ~DisjointSet();

    int getSetsNr() const;

    void printSets() {
        int * viz = new int[subseturiSz]();
        for(int i = 1; i < subseturiSz; i++) {
            cout<<subseturi[i].parinte<<" ";
        }
        cout<<endl;
        delete [] viz;
    }

    map<int, vector<int>> getSets() {
        map<int, vector<int>> sets;
        for(int i = 1; i < subseturiSz; i++) {
            sets[subsetulLui(i)].push_back(i);
//            if(sets.find(subsetulLui(i)) != sets.end()) {
//                sets[subsetulLui(i)].push_back(i);
//            } else {
//                sets[subsetulLui(i)];
//            }
        }
        return sets;
    }
};



#endif //CLUSTERING_DISJOINTSET_H
