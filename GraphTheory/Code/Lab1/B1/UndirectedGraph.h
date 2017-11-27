//
// Created by lucian on 05-Mar-17.
//

#ifndef P2_UNDIRECTEDGRAPH_H
#define P2_UNDIRECTEDGRAPH_H


#include <iostream>
#include <vector>

class UndirectedGraph {
private:
    struct EdgeListNode {
        int tag;
        EdgeListNode* next;
    };

    EdgeListNode** nodes;
    int n, m;

public:
    UndirectedGraph();

    void read(std::istream& in);

    void print(std::ostream& out);

    std::stack<int> getPath(int start, const std::vector<int> &controlPoints);

    virtual ~UndirectedGraph();
};


#endif //P2_UNDIRECTEDGRAPH_H
