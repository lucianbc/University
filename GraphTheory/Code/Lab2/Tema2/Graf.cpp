//
// Created by lucian on 19-Mar-17.
//

#include "Graf.h"

using namespace std;

istream &operator>>(istream &in, Graf &g) {
    in>>g.n>>g.m;
    g.noduri.resize((unsigned int) (g.n + 1));
    for(int i = 0; i <g.m; i++) {
        int u, v;
        in>>u>>v;
        g.noduri[u].vecini.push_back(v);
        g.noduri[v].vecini.push_back(u);
    }
    return in;
}

/**
 * @param i nodul curent
 * @param checked tablul de adevar pentru nodurile vizitate/nevizitate
 * @param t vectorul de parinti in arborele df
 * @param nv nivelul descoperirii nodurilor
 * @param L nivelul minim la care se poate ajunge dintr-un nod
 * @param c tabloul de adevar pentru nodurile critice
 * @param start nodul de start al parcurgerii
 * @param grad_start gradul nodului de start in arborele df
 */
void Graf::df(int i, bool *checked, int *t, int *nv, int *L, int *c, int start, int& grad_start) {
    checked[i] = 1;
    L[i] = nv[i];
    for(int v : noduri[i].vecini) {
        if(!checked[v]) {
            nv[v] = nv[i] + 1;
            t[v] = i;
            if(i == start) grad_start++;
            df(v, checked, t, nv, L, c, start, grad_start);
            if(L[i] > L[v])
                L[i] = L[v];
            if(L[v] >= nv[i])
                c[i] = 1;
        } else {
            if(v != t[i] && L[i] > nv[v])
                L[i] = nv[v];
        }
    }
}

void Graf::GetArticulationPoints() {
    bool *checked = new bool[n + 1]();
    int *t = new int[n + 1]();
    int *nv = new int[n + 1]();
    int *L = new int[n + 1]();
    int *c = new int[n + 1]();

    for(int i = 1; i <= n; i++) {
        if(!checked[i]) {
            nv[i] = 1;
            int root = i;
            int grad_root = 0;
            df(i, checked, t, nv, L, c, root, grad_root);
            c[root] = grad_root > 1;
        }
    }

    for(int i = 1; i <= n; i++) {
        cout<<c[i]<<" ";
    }

    delete [] checked;
    delete [] t;
    delete [] nv;
    delete [] L;
    delete [] c;
}

ostream &operator<<(ostream &out, Graf &g) {
    for(int i = 1; i <= g.n; i++){
        cout<<i<<": ";
        for(int v : g.noduri[i].vecini) {
            cout<<v<<" ";
        }
        cout<<endl;
    }
    return out;
}

void Graf::df_muchii(int i, bool *checked, int *t, int *nv, int *L, vector<Muchie> &muchii) {
    checked[i] = 1;
    L[i] = nv[i];
    for(int v : noduri[i].vecini) {
        if(!checked[v]) {
            nv[v] = nv[i] + 1;
            t[v] = i;
            df_muchii(v, checked, t, nv, L, muchii);
            if(L[i] > L[v])
                L[i] = L[v];
            if(L[v] > nv[i])
                muchii.push_back(Muchie(i, v));
        } else {
            if(v != t[i] && L[i] > nv[v]) {
                L[i] = nv[v];
            }
        }
    }
}

void Graf::GetCriticalEdges() {
    bool *checked = new bool[n + 1]();
    int *t = new int[n + 1]();
    int *nv = new int[n + 1]();
    int *L = new int[n + 1]();

    vector<Muchie> muchiiCritice;

    for(int i = 1; i <= n; i++) {
        if(!checked[i]) {
            nv[i] = 1;
            df_muchii(i, checked, t, nv, L, muchiiCritice);
        }
    }

    for(int i = 0; i < muchiiCritice.size(); ++i) {
        cout<<muchiiCritice[i].u<<" "<<muchiiCritice[i].v<<endl;
    }

    delete [] checked;
    delete [] t;
    delete [] nv;
    delete [] L;
}

