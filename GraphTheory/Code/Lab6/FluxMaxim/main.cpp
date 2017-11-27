#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <cmath>

using namespace std;

typedef std::pair<int, int> muchie;

ostream&operator<<(ostream& out, vector<int> v) {
    for(auto a : v) {
        cout<<a<<" ";
    }
//    cout<<endl;
    return out;
}


struct pair_hash {
    template <class T1, class T2>
    size_t operator () (const pair<T1,T2> &p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);

        return h1 ^ h2;
    }
};

class Graph {
    friend void edmonds_karp(Graph &g);
    friend bool bf(Graph g, vector<int> &path);
    friend ostream&operator<<(ostream& out, Graph g);
    friend void amelioreaza(Graph &g, const vector<int> parents);
    friend bool check(Graph &g);
    friend int printCut(Graph &g, vector<muchie>& muchiiTaietura);
    vector<std::list<int>> adjList;
    vector<std::list<int>> incList;
    unordered_map<std::pair<int, int>, int, pair_hash> capacity;
    unordered_map<std::pair<int, int>, int, pair_hash> flux;
    int n;
    int s, t;
public:
    Graph(int n): n(n), adjList((unsigned long long int) n), incList((unsigned long long int) n) {}

    void addEdge(int u, int v, int cap) {
        adjList[u].push_back(v);
        incList[v].push_back(u);
        capacity[muchie(u, v)] = cap;
        flux[muchie(u, v)] = 0;
    }

    void addEdge(int u, int v, int cap, int fx) {
        adjList[u].push_back(v);
        incList[v].push_back(u);
        capacity[muchie(u, v)] = cap;
        flux[muchie(u, v)] = fx;
    }

    void setStart(int s) { this->s = s; }
    void setSink(int t) { this->t = t; }
};

Graph citire() {
    ifstream fin("graf.in");
    int n, m;
    fin>>n;
    n++;
    Graph g(n);
    int s, t;
    fin>>s>>t;
    g.setSink(t);
    g.setStart(s);
    fin>>m;
    for(int i = 0; i < m; i++) {
        int u, v, c, f;
        fin>>u>>v>>c>>f;
//        cout<<"adaug "<<u<<" "<<v<<endl;
        g.addEdge(u, v, c, f);
//        g.addEdge(u, v, c);
    }
    fin.close();
    return g;
}

ostream&operator<<(ostream& out, Graph g) {
    for(int i = 1; i < g.n; i++) {
        for(int v : g.adjList[i]) {
            cout<<i<<" "<<v<<" "<<g.flux[muchie(i, v)]<<"/"<<g.capacity[muchie(i, v)]<<endl;
        }
    }
    return out;
}

bool bf(Graph g, vector<int> &path) {
    queue<int> myQ;
    vector<int> roots((unsigned long long int) g.n, 0);
    myQ.push(g.s);
    roots[g.s] = g.s;
    while(myQ.size()) {
        int crt = myQ.front();
        myQ.pop();

        if(crt == g.t) {
            int p = roots[abs(crt)];

            do {
                path.push_back(crt);
                crt = p;
                p = roots[abs(crt)];
            } while(abs(p) != abs(crt));

            path.push_back(crt);
            return true;
        }

        for(int a : g.adjList[crt]) {
          if(roots[a] == 0 && g.flux[muchie(crt, a)] < g.capacity[muchie(crt, a)]) {    // muchie directa: trebuie sa mai am loc
              myQ.push(a);
              roots[a] = crt;
            }
        }
        for(int i : g.incList[crt]) {  // muchie de intoarcere: trebuie ca fluxul sa nu fie 0
            if(roots[i] == 0 && g.flux[muchie(i, crt)] > 0) {
                myQ.push(i);
                roots[i] = -crt;
            }
        }
    }

    return false;
}

void amelioreaza(Graph &g, const vector<int> parents) {
    int minDirect = 0x7fffffff;
    int minBack = 0x7fffffff;
    int bottleneck = 0;


    for(int i = (int) (parents.size() - 1); i >= 1; i--) {
        int vs = parents[i - 1];
        int us = parents[i];
        int v = abs(parents[i - 1]);
        int u = abs(parents[i]);
        if(us < 0) {   // muchie de intoarcere
            minBack = g.flux[muchie(v, u)] < minBack ? g.flux[muchie(v, u)] : minBack;
        } else {   // muchie directe
            minDirect = g.capacity[muchie(u, v)] - g.flux[muchie(u, v)] < minDirect ? g.capacity[muchie(u, v)] - g.flux[muchie(u, v)] : minDirect;
        }

        bottleneck = minDirect < minBack ? minDirect : minBack;
    }

    for(int i = (int) (parents.size() - 1); i >= 1; i--) {
        int vs = parents[i - 1];
        int us = parents[i];
        int v = abs(parents[i - 1]);
        int u = abs(parents[i]);
        if(us < 0) {  // muchie de intoarcere
            g.flux[muchie(v, u)] -=  bottleneck;
        } else { // muchie directa
            g.flux[muchie(u, v)] += bottleneck;
        }
    }
}

void edmonds_karp(Graph &g) {
    vector<int> parents;

//    int t = 10;

    while(bf(g, parents)) {
        amelioreaza(g, parents);
        parents.clear();

    }
}

bool check(Graph &g) {
    for(int i = 1; i < g.n; i++) {
        if(i != g.s && i != g.t) {
            int in = 0, out = 0;
            for(int inc : g.incList[i]) {
                if(g.flux[muchie(inc, i)] > g.capacity[muchie(inc, i)]) return false;
                in += g.flux[muchie(inc, i)];
            }
            for(int adj : g.adjList[i]) {
                if(g.flux[muchie(i, adj)] > g.capacity[muchie(i, adj)]) return false;
                out += g.flux[muchie(i, adj)];
            }
        }
    }
    return true;
}

int printCut(Graph &g, vector<muchie>& muchiiTaietura) {
//    vector<muchie> muchiiTaietura;
    queue<int> myQ;
    vector<bool> viz((unsigned long long int) g.n, false);
    myQ.push(g.s);
    viz[g.s] = true;
    int cap = 0;
    while(myQ.size()) {
        int crt = myQ.front();
        myQ.pop();

        for(int a : g.adjList[crt]) {
            if(!viz[a] && g.flux[muchie(crt, a)] < g.capacity[muchie(crt, a)]) {
                myQ.push(a);
                viz[a] = true;
            } else {
                cap += g.flux[muchie(crt, a)];
                muchiiTaietura.push_back(muchie(crt, a));
            }
        }
    }

    return cap;
}

int main() {

    Graph g = citire();

    if(check(g)) {
        cout<<"DA\n";

        edmonds_karp(g);

        cout<<g;

        vector<muchie> taietura;

        cout<<printCut(g, taietura)<<endl;

        for(muchie m: taietura) {
            cout<<m.first<<" "<<m.second<<endl;
        }
    } else {
            cout<<"NU"<<endl;
    }

    return 0;
}