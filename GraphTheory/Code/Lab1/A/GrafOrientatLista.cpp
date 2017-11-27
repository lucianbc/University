//
// Created by lucian on 01-Mar-17.
//

#include "GrafOrientatLista.h"

GrafOrientatLista::GrafOrientatLista() {
    this->n = this->m = -1;
    this->noduri = nullptr;
}

GrafOrientatLista::~GrafOrientatLista() {
    for(int i = 0; i < this->n; i++) {
        Nod* crt = noduri[i];
        while(crt) {
            Nod* tmp = crt->next;
            delete crt;
            crt = tmp;
        }
    }
    if(noduri) delete[](noduri);
}

void GrafOrientatLista::afisare(std::ostream &fout) {
    for(int i = 0; i < this->n; i++) {
        fout<<i + 1 <<": ";
        GrafOrientatLista::Nod* crt = this->noduri[i];
        while(crt) {
            fout<<crt->val + 1 <<" ";
            crt = crt->next;
        }
        fout<<std::endl;
    }
}

void GrafOrientatLista::citire(std::istream &fin) {
    fin>>this->n>>this->m;

    noduri = new GrafOrientatLista::Nod*[this->n]();

    for(int i = 0; i < this->m; i++) {
        int u, v;
        fin>>u>>v;
        u--; v--;
        GrafOrientatLista::Nod* nod = new GrafOrientatLista::Nod;
        nod->val = v;
        nod->next = this->noduri[u];
        this->noduri[u] = nod;
    }
}
