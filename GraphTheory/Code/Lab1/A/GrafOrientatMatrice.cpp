//
// Created by lucian on 01-Mar-17.
//

#include "GrafOrientatMatrice.h"

int** aloca2d(int n, int m) {
    int **a = new int*[n]();
    for(int i = 0; i < n; i++) {
        a[i] = new int[m]();
    }
    return a;
}

GrafOrientatMatrice::GrafOrientatMatrice() {
    this->map = nullptr;
    this->m = this->n = -1;
}

void GrafOrientatMatrice::citire(std::istream &fin) {
    fin>>this->n>>this->m;
    this->map = aloca2d(this->n, this->n);
    for(int i = 0; i < m; i++) {
        int u, v;
        fin>>u>>v;
        this->map[--u][--v]++;
    }
}

void GrafOrientatMatrice::afisare(std::ostream &fout) {
    for(int i = 0; i < this->n; i++) {
        fout<<i + 1 <<": ";
        for(int j = 0; j < this->n; j++) {
            if((this->map)[i][j])
                fout<<j + 1 <<" ";
        }
        fout<<std::endl;
    }
}

GrafOrientatMatrice::~GrafOrientatMatrice() {
    for(int i = 0; i < this->n; i++) {
        if(map[i]) delete[](map[i]);
    }
    if(map) delete[](map);
}
