//
// Created by Lucian on 05/05/2017.
//

#ifndef SECONDMST_GRAFPONDERAT_H
#define SECONDMST_GRAFPONDERAT_H


#include <queue>
#include <vector>
#include <sstream>
#include <iostream>
#include "DisjointSet.h"
#include <list>
#include <set>

using namespace std;

struct Muchie {
    int c1, c2, pondere;

    Muchie(int c1, int c2, int pondere);

    string toString() const;

    void print() const {
        cout<<c1<<" "<<c2<<" "<<pondere<<endl;
    }
};

struct Comparator {
    bool operator()(Muchie m1, Muchie m2);
};

struct AdjListEl {
    int vecin;
    int pondere;

    AdjListEl(int vecin, int pondere);
};

class GrafPonderat {

    typedef priority_queue<Muchie, vector<Muchie>, Comparator> minHeapMuchii;

private:
    minHeapMuchii muchii;
    int N, M;
    vector<list<AdjListEl>> grafAdjList;
    int cost;

public:

    GrafPonderat(int N);

    void adaugaMuchie(int c1, int c2, int pondere);

    int getN() const;

    void setN(int N);

    int getM() const;

    void setM(int M);

    void printAdjList() {
        for(int i = 1; i <= N; i++) {
            for(AdjListEl x : grafAdjList[i]) {
                cout<<"("<<x.vecin<<","<<x.pondere<<") ";
            }
            cout<<endl;
        }
    }

    void print() {
        cout<<"cost: "<<cost<<endl;
//        cout<<N<<" "<<M<<endl;
        minHeapMuchii muchiilocal = muchii;

        while(muchiilocal.size()) {
            cout<<muchiilocal.top().toString()<<endl;
            muchiilocal.pop();
        }
    }

    GrafPonderat kruscal() {
        GrafPonderat mst(N);

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

    GrafPonderat kruscal(minHeapMuchii &neadaugate) {
        GrafPonderat mst(N);

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
            } else {
                neadaugate.push(Muchie(crtM.c1, crtM.c2, crtM.pondere));
            }
        }
        return mst;
    }


    Muchie maxBetween(int start, int end) {
        struct arbodeDfsCheck {
            int parent;
            int pondere;
        } viz[N + 1];

        for(int i = 0; i < N + 1; i++) {
            viz[i].parent = viz[i].pondere = 0;
        }

        bool gasit = false;

        Muchie max(0, 0, 0x80000000);

        queue<int> coada;
        coada.push(start);
        viz[start].parent = start;
        while(coada.size() && !gasit) {
            int crt = coada.front();
            coada.pop();
            for(auto x : grafAdjList[crt]) {
                if(viz[x.vecin].parent == 0) {
                    viz[x.vecin].parent = crt;
                    viz[x.vecin].pondere = x.pondere;
                    coada.push(x.vecin);
                }
                if(x.vecin == end) {
                    gasit = true;
                    int cnode = x.vecin;
                    do {
                        if(viz[cnode].pondere > max.pondere) {
                            max.c1 = cnode;
                            max.c2 = viz[cnode].parent;
                            max.pondere = viz[cnode].pondere;
                        }
                        cnode = viz[cnode].parent;
                    } while(cnode != viz[cnode].parent);
                }
            }
        }
        return max;
    }

    GrafPonderat secondmst() {
        minHeapMuchii neadaugate;

        GrafPonderat mst = kruscal(neadaugate);

        Muchie inlocuita(0, 0, 0);
        Muchie inlocuitor(0, 0, 0);
        int dif = 0x7fffffff;

//        cout<<"neadaugate:\n";
        while(neadaugate.size()) {
//            neadaugate.top().print();
//            neadaugate.pop();
            Muchie max = mst.maxBetween(neadaugate.top().c2, neadaugate.top().c1);
//            cout<<"max between "<<neadaugate.top().c2<<" "<<neadaugate.top().c1<<": ";
//            max.print();
            if(abs(max.pondere - neadaugate.top().pondere) <= dif) {
                dif = abs(max.pondere - neadaugate.top().pondere);
                inlocuita = max;
                inlocuitor = neadaugate.top();
            }
            neadaugate.pop();
        }

        if(dif != 0x7fffffff) {
            minHeapMuchii muchiiNoi;

            while(mst.muchii.size()) {
                if(mst.muchii.top().c1 == inlocuita.c1 && mst.muchii.top().c2 == inlocuita.c2 &&
                   mst.muchii.top().pondere == inlocuita.pondere) {
                    muchiiNoi.push(inlocuitor);
                } else {
                    muchiiNoi.push(mst.muchii.top());
                }

                mst.muchii.pop();
            }

            mst.muchii = muchiiNoi;
            mst.cost += dif;
        }

        return mst;
    }

};


#endif //SECONDMST_GRAFPONDERAT_H
