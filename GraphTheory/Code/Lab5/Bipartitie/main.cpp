#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

/*
 * Graf cu n noduri numerotate de la 0 la n - 1
 */
class Graph {
    int n; // numarul de noduri
    vector<list<int>> adj;

    friend void checkBipartite(const Graph& g);

public:
    Graph(int n) : n(n), adj((unsigned long) n) {}
    void addEdge(int u, int v);
    void print();
    int getVerticesNumber() const;

};

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int Graph::getVerticesNumber() const { return n; }


void Graph::print() {
    int ct = 0;
    for(auto l : adj) {
        cout<<ct<<": ";
        for(auto n : l) {
            cout<<n<<" ";
        }
        cout<<endl;
        ct++;
    }
}

void checkBipartite(const Graph& g){
    vector<int> parent((unsigned long) g.getVerticesNumber(), -1);
    vector<int> color((unsigned long) g.getVerticesNumber(), 0);
    for(int crt = 0; crt < parent.size(); ++crt) {
        if(parent[crt] == -1) {
            stack<int> stack;
            stack.push(crt);
            parent[crt] = crt;
            color[crt] = 1;
            while(stack.size()) {
                int s = stack.top();
                stack.pop();
                for(auto v : g.adj[s]) {
                    if(parent[v] == -1) { // daca nodul nu e vizitat
                        parent[v] = s;
                        color[v] = color[s] == 1 ? 2 : 1;
                        stack.push(v);
                    } else { // daca nodul e vizitat, e si colorat
                        if(color[s] == color[v]) {
                            cout<<"ciclu: ";
                            int root = parent[v];
                            cout<<root<<" "<<v<<" ";
                            while(s != root) {
                                cout<<s<<" ";
                                s = parent[s];
                            }
                            cout<<s<<endl;
                            return;
                        }
                    }
                }
            }
        }
    }
    cout<<"graful este bipartit\n";
    cout<<"1: ";
    for(int i = 0; i < color.size(); i++) {
        if(color[i] == 1)
            cout<<i<<' ';
    }
    cout<<endl;
    cout<<"2: ";
    for(int i = 0; i < color.size(); i++) {
        if(color[i] == 2)
            cout<<i<<' ';
    }
    cout<<endl;
}

Graph citire() {
    ifstream fin("graf.in");
    int nrN, nrM;
    fin>>nrN>>nrM;

    Graph g(nrN);

    for(int i = 1; i <= nrM; i++) {
        int u, v;
        fin>>u>>v;
        g.addEdge(u, v);
    }

    return g;
}

int main() {

    Graph g(8);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(4, 6);
    g.addEdge(4, 5);
    g.addEdge(2, 7);
    g.addEdge(3, 7);
    g.addEdge(5, 6);
    g.print();

//    checkBipartite(g);

    return 0;
}