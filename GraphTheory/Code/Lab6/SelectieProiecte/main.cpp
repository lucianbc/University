#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <cmath>

#define INF 0x7fffffff

typedef std::pair<int, int> muchie;

using namespace std;

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
    friend Graph citire(int &pc);
    friend int getCut(Graph &g, vector<muchie>& muchiiTaietura, vector<int> &cut);
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

    void setStart(int s) { this->s = s; }
    void setSink(int t) { this->t = t; }

    int getStart() { return s; }
};

Graph citire(int &pc) {
    ifstream fin("graf.in");
    pc = 0;
    int n, m;
    fin>>n>>m;
    n++;
    Graph g(n + 2);
    g.setStart(n);
    g.setSink(n + 1);
    vector<int> cost((unsigned long long int) n);
    for(int i = 1; i < n; i++) {
        fin>>cost[i];
    }
    for(int i = 0; i < m; i++) {
        int u, v;
        fin>>u>>v;
        g.addEdge(u, v, INF);
    }

    for(int i = 1; i < n; i++) {
        if(cost[i] < 0) g.addEdge(i, g.t, -cost[i]);
        if(cost[i] > 0) {
            g.addEdge(g.s, i, cost[i]);
            pc += cost[i];
        }
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

    int t = 10;

    while(bf(g, parents) && t) {
        amelioreaza(g, parents);
        parents.clear();
        t--;
    }
}

int getCut(Graph &g, vector<muchie>& muchiiTaietura, vector<int> &cut) {
//    vector<muchie> muchiiTaietura;
    queue<int> myQ;
    vector<bool> viz((unsigned long long int) g.n, false);
    vector<bool> reachable((unsigned long long int) g.n, false);
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
            }
        }

        for(int i : g.incList[crt]) {
            if(!viz[i] && g.flux[muchie(i, crt)] > 0) {
                myQ.push(i);
                viz[i] = true;
            }
        }
    }

    for(auto m : g.flux) {
        muchie mch = m.first;
        if(viz[mch.first] == 1 && viz[mch.second] == 0) {
            muchiiTaietura.push_back(mch);
            cap += m.second;
        }
    }

    cut.clear();
    for(int x : viz) {
        cut.push_back(x);
    }

    return cap;
}

int main() {

    int pozitiveCosts;

    Graph g = citire(pozitiveCosts);

    edmonds_karp(g);

    vector<muchie> taietura;

    vector<int> cut;

    int cap = getCut(g, taietura, cut);

    cout<<"profit: "<<pozitiveCosts - cap<<endl;

    cout<<"Activitati selectate: ";

    for (int i = 1; i < cut.size(); i++) {
        if(cut[i] && i != g.getStart()) cout<<i<<" ";
    }

    cout<<endl;

    return 0;
}