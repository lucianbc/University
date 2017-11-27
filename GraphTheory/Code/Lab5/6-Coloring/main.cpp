#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

class Graph {
    int n; // numarul de noduri
    vector<list<int>> adj;

    friend void sixColor(Graph g);

    friend Graph citire();

public:
    Graph(int n) : n(n + 1), adj((unsigned long) (n + 1)) {}

    void addEdge(int u, int v);
};

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void sixColor(Graph g) {
    vector<set<int>> listaPeGrade((unsigned long) g.n); // listaPeGrade[x] -> toate nodurile de grad x
    vector<int> grad((unsigned long) g.n); // grad[x] -> gradul lui x

    for(int i = 1; i <= g.n; i++) {
        listaPeGrade[g.adj[i].size()].insert(i);
        grad[i] = (int) g.adj[i].size();
    }

    vector<int> label((unsigned long) g.n);

    for(int i = label.size() - 1; i > 0; i--) {
        for(int j = 0; j < listaPeGrade.size(); j++) {
            if(listaPeGrade[j].size() > 0) {
                label[j] = i; // eticheta lui j este i -> (n, n-1, ..., 1)

                break;
            }
        }
    }
}

Graph citire() {
    ifstream fin("graf.in");
    int n, m;
    fin>>n>>m;

    Graph g(n);

    for(int i = 0; i < m; i++) {
        int u, v;
        fin>>u>>v;
        g.addEdge(u, v);
    }

    return g;
}

int main() {

    Graph g = citire();

    return 0;
}