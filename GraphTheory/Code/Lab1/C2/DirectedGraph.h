//
// Created by lucian on 05-Mar-17.
//

#ifndef P2_UNDIRECTEDGRAPH_H
#define P2_UNDIRECTEDGRAPH_H


#include <iostream>
#include <vector>
#include <stack>

class DirectedGraph {
private:
    struct EdgeListNode {
        int tag;
        EdgeListNode* next;
    };

    EdgeListNode** nodes;
    int n, m; // n nodes, m vertecies

public:
    DirectedGraph();

    void read(std::istream& in);

    void print(std::ostream& out);

    std::stack<int> getPath(int start, const std::vector<int> &controlPoints);

    bool isAcyclic();

    virtual ~DirectedGraph();
};


#endif //P2_UNDIRECTEDGRAPH_H
