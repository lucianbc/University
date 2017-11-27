//
// Created by lucian on 05-Mar-17.
//

#include <queue>
#include <stack>
#include "DirectedGraph.h"

using namespace std;

DirectedGraph::DirectedGraph() : nodes(nullptr), n(0), m(0) {}

void DirectedGraph::read(istream &in) {
    in>>n>>m;
    nodes = new EdgeListNode*[n]();
    for(int i = 0; i < m; i++) {
        EdgeListNode* u = new EdgeListNode;
        EdgeListNode* v = new EdgeListNode;

        in>>u->tag; u->tag--;
        in>>v->tag; v->tag--;

        //cout<<"("<<u->tag<<", "<<v->tag<<")\n";

        v->next = nodes[u->tag];
        nodes[u->tag] = v;
    }
}

DirectedGraph::~DirectedGraph() {
    if(nodes != nullptr) {
        for(int i = 0; i < n; i++) {
            EdgeListNode* crt = nodes[i];
            while (crt) {
                EdgeListNode* tmp = crt->next;
                delete crt;
                crt = tmp;
            }
        }
        delete nodes;
    }
}

void DirectedGraph::print(ostream &out) {
    for(int i = 0; i < n; i++) {
        out<<i + 1<<": ";
        EdgeListNode* crt = nodes[i];
        while (crt) {
            out<<crt->tag + 1<<" ";
            crt = crt->next;
        }
        out<<endl;
    }
}

stack<int> DirectedGraph::getPath(int start, const vector<int> &controlPoints) {
    int *paths = new int[n]();
    for(int p : controlPoints) paths[p] = -1;
    
    stack<int> path;

    queue<int> checked;

    if(paths[start] != -1)
        checked.push(start);
    else {
        path.push(start);
        return path;
    }

    bool found = false;

    while(checked.size() && !found) {
        int crt = checked.front();
        checked.pop();

        EdgeListNode* nbs = nodes[crt];
        while (nbs) {
            if(paths[nbs->tag] == -1) {
                found = true;
                path.push(nbs->tag);
                int c = crt;
                while(c != start) {
                    path.push(c);
                    c = paths[c];
                }
                path.push(start);
                break;
            } else if(paths[nbs->tag] == 0 && nbs->tag != start) {
                paths[nbs->tag] = crt;
                checked.push(nbs->tag);
            }

            nbs = nbs->next;
        }
    }
    return path;
}

bool DirectedGraph::isAcyclic() {

    stack<int> branch;

    vector<int> parents((unsigned int) n, -1);
    vector<int> isChecked((unsigned int) n, false);

    for(int i = 0; i < n; i++) {
        if(parents[i] == -1) {
            parents[i] = i;
            branch.push(i);

            while (!branch.empty()) {
                int crt = branch.top();
                branch.pop();

                cout<<crt<<" ";

                EdgeListNode* c = nodes[crt];

                while (c) {
                    if(parents[c->tag] == -1) {
                        parents[c->tag] = crt;
                        branch.push(c->tag);
                    } else {
                        cout<<"\n inapoi: ";

                    }
                    c = c->next;
                }
            }
        }
        cout<<endl;
    }

    return true;
}
