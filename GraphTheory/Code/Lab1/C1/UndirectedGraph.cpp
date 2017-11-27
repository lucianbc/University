//
// Created by lucian on 05-Mar-17.
//

#include <queue>
#include <stack>
#include "UndirectedGraph.h"

using namespace std;

UndirectedGraph::UndirectedGraph() : nodes(nullptr), n(0), m(0) {}

void UndirectedGraph::read(istream &in) {
    in>>n>>m;
    nodes = new EdgeListNode*[n]();
    for(int i = 0; i < m; i++) {
        EdgeListNode* u = new EdgeListNode;
        EdgeListNode* v = new EdgeListNode;

        in>>u->tag; u->tag--;
        in>>v->tag; v->tag--;

        //cout<<"("<<u->tag<<", "<<v->tag<<")\n";

        u->next = nodes[v->tag];
        nodes[v->tag] = u;

        v->next = nodes[u->tag];
        nodes[u->tag] = v;
    }
}

UndirectedGraph::~UndirectedGraph() {
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

void UndirectedGraph::print(ostream &out) {
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

stack<int> UndirectedGraph::getPath(int start, const vector<int> &controlPoints) {
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

bool UndirectedGraph::isAcyclic() {

    stack<int> branch;

    vector<int> parents((unsigned int) n, -1);
    vector<int> isChecked((unsigned int) n, false);

    for(int i = 0; i < n; i++) {
        if(!isChecked[i]) {
            branch.push(i);
            parents[i] = i;
            // starting a dfs with the root in the i-th node

            while(!branch.empty()) {
                int s = branch.top();
                branch.pop();
                int p = parents[s];

                if(!isChecked[s]) {
                    //cout<<s<<" ";
                    isChecked[s] = true;
                }

                EdgeListNode* crt = nodes[s];
                while (crt) {
                    if(!isChecked[crt->tag]) {
                        branch.push(crt->tag);
                        parents[crt->tag] = s;
                    }
                    else if(crt->tag != p) {
                        // cout<<s<<" "<<crt->tag<<" parinte: "<<p<<endl;
                        // sunt in 5(s), vreau sa bag 2(crt->tag), care-i vizitat si e diferit de 4(p), care-i parinte
                        // o iau pe la 4 si merg in sus, prin parinti, pana dau de 2

                        cout<<"\nciclu: \n";

                        cout<<crt->tag + 1<<" "<<s + 1<<" "; // nodul curent

                        while(p != crt->tag) {
                            cout<<p + 1<<" ";
                            p = parents[p];
                        }  // parintii, mai putin "radacina" ciclului

                        cout<<crt->tag + 1<<endl;

                        return false;
                    }
                    crt = crt->next;
                }
            }
        }
    }

    return true;
}
