#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <fstream>

#define N_INF 0x80000000

using namespace std;

struct AdjListNode {
    int node;
    int weight;

    AdjListNode(int node, int weight) : node(node), weight(weight) {}
};

struct ProgramareMinima {
    vector<int> distances;
    vector<int> urmatori;
};

class Graph {
    vector<list<AdjListNode>> adjList;
    vector<int> costs;
    int n; // nr de noduri

    int start, finish;

    void topologicalSortUtil(int crt, vector<bool> &visited, stack<int> &s);

    friend Graph citire();

public:
    int getStart() const;

    void setStart(int start);

    int getFinish() const;

    void setFinish(int finish);

    Graph(int n) : n(n), adjList((unsigned long) n), costs((unsigned long) n) {}

    void addEdge(int u, int v, int w);

    stack<int> topologicalSort() {
        stack<int> sort;

        vector<bool> visited((unsigned long) n, false);

        for(int i = 0; i < n; i++) {
            if(!visited[i])
                topologicalSortUtil(i, visited, sort);
        }

        return sort;
    }

    ProgramareMinima getLongestPath();

    void print();

    void printCriticalPath();

    void getSchedule();
};

void Graph::topologicalSortUtil(int crt, vector<bool> &visited, stack<int> &s) {
    visited[crt] = true;

    for(auto v : adjList[crt]) {
        if(!visited[v.node]) {
            topologicalSortUtil(v.node, visited, s);
        }
    }

    s.push(crt);
}

ProgramareMinima Graph::getLongestPath() {
    vector<int> distances((unsigned long) n, N_INF);

    stack<int> topoSort = topologicalSort();

    distances[start] = 0;

    vector<int> urmator((unsigned long) n);

    while(topoSort.size()) {
        int crt = topoSort.top();
        topoSort.pop();
        if(distances[crt] != N_INF) {
            for(auto v : adjList[crt]) {
                if(distances[v.node] < distances[crt] + v.weight) {
                    distances[v.node] = distances[crt] + v.weight;
                    urmator[crt] = v.node;
                }
            }
        }
    }

    return ProgramareMinima { distances, urmator };
}

void Graph::addEdge(int u, int v, int w) {
    adjList[u].push_back(AdjListNode(v, w));
}

Graph citire() {
    int nrV;
    ifstream fin("activitati.txt");
    fin>>nrV;

//    vector<int> costs((unsigned long) nrV);
    Graph g(nrV + 2);

    for(int i = 0; i < nrV; i++) {
        fin>>g.costs[i];
    }

    int nrT;
    fin>>nrT;

    vector<int> gradIntern((unsigned long) nrV, 0);
    vector<int> gradExtern((unsigned long) nrV, 0);

    for(int i = 0; i < nrT; i++) {
        int u, v;
        fin>>u>>v;
        u--; v--;
        g.adjList[u].push_back(AdjListNode(v, g.costs[u]));
        gradIntern[v]++;
        gradExtern[u]++;
    }


//    nrV++;
    g.start = nrV;

    nrV++;
    g.finish = nrV;

    for(int i = 0; i < nrV - 1; i++) {
        if(gradIntern[i] == 0) {
            g.addEdge(g.start, i, 0);
        } else if(gradExtern[i] == 0) {
            g.addEdge(i, g.finish, g.costs[i]);
        }
    }

    fin.close();

    return g;
//    return Graph(0);
}

int Graph::getStart() const {
    return start;
}

void Graph::setStart(int start) {
    Graph::start = start;
}

int Graph::getFinish() const {
    return finish;
}

void Graph::setFinish(int finish) {
    Graph::finish = finish;
}

void Graph::print() {
    for(int i = 0; i < adjList.size(); i++) {
        cout<<i<<": ";
        for(auto v : adjList[i]) {
            cout<<"("<<v.node<<", "<<v.weight<<"), ";
        }
        cout<<endl;
    }
}

void Graph::getSchedule() {
    vector<int> distances = getLongestPath().distances;
    for(int i = 0; i < distances.size() - 2; i++) {
        cout<<i + 1<<": "<<distances[i]<<" - "<<distances[i] + costs[i]<<endl;
    }
}

void Graph::printCriticalPath() {

    ProgramareMinima progMin = getLongestPath();

    cout<<"Durata minima: "<<progMin.distances[finish]<<endl;
    cout<<"Critical Path: ";
    int crt = progMin.urmatori[start];
    while(crt != finish) {
        cout<<crt<<" ";
        crt = progMin.urmatori[crt];
    }
    cout<<endl;

}


int main() {

    Graph g = citire();

//    g.print();

    g.printCriticalPath();

    g.getSchedule();




    return 0;
}