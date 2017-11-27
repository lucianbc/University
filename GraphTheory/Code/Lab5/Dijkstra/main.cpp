#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <queue>
#include <cmath>

#define INF 0x7fffffff

using namespace std;

struct AdjListNode {
    int node;
    int weight;

    AdjListNode(int node, int weight) : node(node), weight(weight) {}
};

struct comparator {
    bool operator()(const AdjListNode& l, const AdjListNode& r) {
        return l.weight < r.weight;
    }
};

class Graph {
    vector<list<AdjListNode>> adjList;

    int n;

    friend Graph citire();

    friend void dijsktra(const Graph &g, int start, const vector<bool> &controlPts);

    friend void drumDeProbMaxima(const Graph &g, int start, int fin);

public:
    Graph(int n) : n(n), adjList((unsigned long) n) {}

    void print();

    int getN() const;
};

Graph citire() {
    int n, m;
    ifstream fin("grafpond.in");
    fin>>n>>m;
    Graph g(n);

    for(int i = 1; i <= m; i++) {
        int u, v, w;
        fin>>u>>v>>w;
        u--;
        v--;
        g.adjList[u].push_back(AdjListNode(v, w));
        g.adjList[v].push_back(AdjListNode(u, w));
    }

    fin.close();

    return g;
}

void Graph::print() {
    for(int i = 0; i < adjList.size(); i++) {
        cout<<i + 1<<": ";
        for(auto v : adjList[i]) {
            cout<<"("<<v.node + 1<<", "<<v.weight<<"), ";
        }
        cout<<endl;
    }
}

int Graph::getN() const {
    return n;
}

void drumDeProbMaxima(const Graph &g, int start, int fin) {
    vector<int> distances((unsigned long) g.getN(), INF);

    vector<int> parents((unsigned long) g.getN(), 0);

    priority_queue<AdjListNode, vector<AdjListNode>, comparator> myPq;

    myPq.push(AdjListNode(start, 0));

    parents[start] = start;

    distances[start] = 0;

    while(myPq.size()) {
        AdjListNode crt = myPq.top();
        myPq.pop();

        for(auto v : g.adjList[crt.node]) {
            if(distances[v.node] > distances[crt.node] + v.weight) {
                distances[v.node] = distances[crt.node] + v.weight;
                myPq.push(AdjListNode(v.node, distances[v.node]));
                parents[v.node] = crt.node;
            }
        }
    }

    double p = 1l / pow(2, distances[fin]);

    cout<<"probabilitatea celui mai sigur drum este: "<<p<<", iar drumul este:";

    int crt = fin;

    while(parents[crt] != crt) {
        cout<<crt + 1<<" ";
        crt = parents[crt];
    }
    cout<<crt + 1<<endl;
}

void dijsktra(const Graph &g, int start, const vector<bool> &controlPts) {
    vector<int> distances((unsigned long) g.getN(), INF);

    vector<int> parents((unsigned long) g.getN(), 0);

    int nearestControl = -1;
    int smallestDistance = INF;

    priority_queue<AdjListNode, vector<AdjListNode>, comparator> myPq;

    myPq.push(AdjListNode(start, 0));

    parents[start] = start;

    distances[start] = 0;

    while(myPq.size()) {
        AdjListNode crt = myPq.top();
        myPq.pop();

        for(auto v : g.adjList[crt.node]) {
            if(distances[v.node] > distances[crt.node] + v.weight) {
                distances[v.node] = distances[crt.node] + v.weight;
                myPq.push(AdjListNode(v.node, distances[v.node]));
                parents[v.node] = crt.node;
                if(controlPts[v.node] && distances[v.node] < smallestDistance) {
                    smallestDistance = distances[v.node];
                    nearestControl = v.node;
                }
            }
        }
    }

    cout<<"cel mai apropiat punct de control este "<<nearestControl + 1<<" la o distanta de "<<distances[nearestControl]<<endl;

    int crt = nearestControl;

    while(parents[crt] != crt) {
        cout<<crt + 1<<" ";
        crt = parents[crt];
    }
    cout<<crt + 1<<endl;
}

void citirePuncteControl(vector<bool> &set, int &start) {
    int k;
    ifstream fin("puncteControl.txt");

    cout<<fin.is_open()<<endl;

    fin>>k;
    for(int i = 0; i < k; i++) {
        int x;
        fin>>x;
        x--;
        set[x] = true;
    }

    fin>>start;

    start--;

    fin.close();
}



int main() {

    Graph g = citire();

    g.print();

    vector<bool> controlPoints((unsigned long) g.getN(), false);

    int start;

    citirePuncteControl(controlPoints, start);

    dijsktra(g, start, controlPoints);

    return 0;
}