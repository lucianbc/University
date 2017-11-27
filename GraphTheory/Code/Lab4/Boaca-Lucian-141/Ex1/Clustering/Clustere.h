//
// Created by Lucian on 04/05/2017.
//

#ifndef CLUSTERING_CLUSTERE_H
#define CLUSTERING_CLUSTERE_H


#include <queue>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "DisjointSet.h"
#include <unordered_map>
#include <set>

using namespace std;

struct Muchie {
    int c1, c2, pondere;

    Muchie(int c1, int c2, int pondere);

    string toString() const;
};

struct Comparator {
    bool operator()(Muchie m1, Muchie m2);
};

class Clustere;

typedef priority_queue<Muchie, vector<Muchie>, Comparator> minHeapMuchii;

class GrafPonderat {

    friend class Clustere;

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
        mst.M = 0;
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


class Clustere {
private:
    GrafPonderat graf;
    vector<string> words;

    int k;

private:

    int distanta(const char *s1, const char *s2){
        int n1=strlen(s1); int n2=strlen(s2);
        int *ci1=new int[n2+1]; int *ci=new int[n2+1];
        for(int j=0;j<=n2;j++) ci1[j]=j;
        for(int i=1;i<=n1;i++){
            ci[0]=i;
            for(int j=1;j<=n2;j++)
                if(s1[i-1]==s2[j-1]) ci[j]=ci1[j-1];
                else ci[j]=1+min(min(ci1[j],ci[j-1]),ci1[j-1]) ;
            for(int j=0;j<=n2;j++) ci1[j]=ci[j];
        }
        return ci[n2];
    }

public:
    void citire() {
        words.push_back("");
        cin>>k;
        ifstream fin("cuvinte.in");
        string word;
        while(fin >> word) {
            words.push_back(word);
            for(int i = words.size() - 2; i >= 1; i--) {
//                cout<<word<<" "<<words[i]<<" "<<distanta(word.c_str(), words[i].c_str())<<endl;
                graf.adaugaMuchie(words.size() - 1, i, distanta(word.c_str(), words[i].c_str()));
            }
        }
        graf.setN(words.size() - 1);

//        graf.print();

        fin.close();
    }

    void testKruscal(){
        GrafPonderat g = graf.kruscal();
        g.print();
    }

    void cluster() {
        DisjointSet sets(graf.getN() + 1);
        minHeapMuchii muchii = graf.muchii;
        while(sets.getSetsNr() > k) {
            Muchie crtM = muchii.top();
            muchii.pop();
            int c1Set = sets.subsetulLui(crtM.c1);
            int c2Set = sets.subsetulLui(crtM.c2);
            if(c1Set != c2Set) {
                sets.uneste(crtM.c1, crtM.c2);
            }
        }
        map<int, vector<int>> clusters = sets.getSets();
        for(auto k : clusters) {
            for(auto x : k.second) {
                cout<<words[x]<<" ";
            }
            cout<<endl;
        }

        // operatiile din structura de date 'set' se fac in timp logaritmic, aceasta structura
        // fiind organizata ca un arbore echilibrat, deci complexitatea afisarii este mai mica
        // decat O(kˆ2*log(k)) < O(nˆ2)
        set<pair<int, int>> classes;

        for(auto c1 : clusters) {
            for(auto c2 : clusters) {
                pair<int, int> myPair(c1.first, c2.first);
                classes.insert(myPair);
            }
        }

        while(muchii.size() && classes.size()) {
            Muchie crtM = muchii.top();
            muchii.pop();
            set<pair<int, int>>::iterator it = classes.find(pair<int, int>(crtM.c1, crtM.c2));
            // muchiile sunt sortate in heap, deci distanta dintre doua clustere este data de prima aparitie
            // a unei muchii formate din doi reprezentanti ai celor doua clustere
            if(it != classes.end()) {
                cout<<"distanta dintre clasele "<<crtM.c1<<" si "<<crtM.c2<<" este "<<crtM.pondere<<endl;
                classes.erase(it);
                classes.erase(classes.find(pair<int, int>(crtM.c2, crtM.c1)));
            }
        }
    }
};


#endif //CLUSTERING_CLUSTERE_H
