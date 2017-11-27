//
// Created by lucian on 18-Mar-17.
//

#include "Graph.h"

int Graph::translateVertex(int num_vertex) {
    return num_vertex + 1;
}

istream &operator>>(istream& in, Graph &graph) {
    in>>graph.num_vertices>>graph.num_edges;
    graph.vertex_adj_lists = new LinkedList<int>[graph.num_vertices];
    for(int i = 0; i < graph.num_edges; i++) {
        int u, v;
        in>>u>>v;
        u--; v--;
        graph.vertex_adj_lists[u].pushBack(v);
        graph.vertex_adj_lists[v].pushBack(u);
    }
    return in;
}

ostream &operator<<(ostream &out, Graph &graph) {
    for(int i = 0; i < graph.num_vertices; i++) {
        for(int v : graph.vertex_adj_lists[i]) {
            if(v > i)
                out<<graph.translateVertex(i)<<" "<<graph.translateVertex(v)<<endl;
        }
    }

    return out;
}

int Graph::getEdgesNumber() { return num_edges; }


LinkedList<int> * Graph::BreadthFirstTraversal() {
    return Traverse(&LinkedList<int>::pushBack);
}

LinkedList<int> *Graph::DepthFirstTraversal() {
    return Traverse(&LinkedList<int>::pushFront);
}

LinkedList<int> *Graph::Traverse(void (LinkedList<int>::*push_endpoint)(int)) {
    bool *visited = new bool[num_vertices]();
    LinkedList<int> *traversal = new LinkedList<int>;

    for(int i = 0; i < num_vertices; i++) {
        if(!visited[i]) {
            LinkedList<int>* comp = TraverseComponent(push_endpoint, visited, i);
            traversal->append(*comp);
            delete comp;
        }
    }
    return traversal;
}

LinkedList<int> *Graph::TraverseComponent(void (LinkedList<int>::*push_endpoint)(int), bool *checked, int seed) {
    LinkedList<int> *structure = new LinkedList<int>;
    LinkedList<int> *traversal = new LinkedList<int>;

    (structure->*push_endpoint)(seed);
    traversal->pushBack(seed);
    checked[seed] = true;

    while (structure->getLength()) {
        int crt = *structure->begin();
        structure->removeFront();
        for(int v : vertex_adj_lists[crt]) {
            if(!checked[v]) {
                (structure->*push_endpoint)(v);
                traversal->pushBack(v);
                checked[v] = true;
            }
        }
    }
    delete structure;
    return traversal;
}

LinkedList<LinkedList<int> *> *Graph::GetConnectedComponents() {
    LinkedList<LinkedList<int> *> *components = new LinkedList<LinkedList<int> *>;

    bool *visited = new bool[num_vertices]();
    for(int i = 0; i < num_vertices; i++) {
        if(!visited[i]) {
            components->pushBack(TraverseComponent(&LinkedList<int>::pushBack, visited, i));
        }
    }

    return components;
}

bool Graph::isConnected() {
    LinkedList<LinkedList<int> *> *components = GetConnectedComponents();
    bool resp = components->getLength() > 1;

    for(LinkedList<int> *l : *components) {
        delete l;
    }

    delete components;

    cout<<components->getLength()<<endl;

    return resp;
}

Graph Graph::operator+(Graph &other){
    Graph tmp;

    if(this->num_vertices == other.num_vertices) {
        tmp.num_vertices = this->num_vertices;
        tmp.vertex_adj_lists = new LinkedList<int>[tmp.num_vertices];
        int nr_endpoints = 0;
        for(int i = 0; i < num_vertices; i++) {
            bool *checked = new bool[num_vertices]();
            for(int v : this->vertex_adj_lists[i]) {
                tmp.vertex_adj_lists[i].pushBack(v);
                checked[v] = true;
                nr_endpoints++;
            }
            for(int v : other.vertex_adj_lists[i]) {
                if(!checked[v]) {
                    tmp.vertex_adj_lists[i].pushBack(v);
                    nr_endpoints++;
                }
            }
        }
        tmp.num_edges = nr_endpoints / 2;
    }

    return tmp;
}

Graph::Graph() : num_edges(0), num_vertices(0), vertex_adj_lists(nullptr) {}

Graph::~Graph() {
    delete[](vertex_adj_lists);
}

Graph::Graph(const Graph &other) {
    num_edges = other.num_edges;
    num_vertices = other.num_vertices;
    vertex_adj_lists = new LinkedList<int>[num_vertices];
    for(int i = 0; i < num_vertices; i++) {
        vertex_adj_lists[i] = other.vertex_adj_lists[i];
    }
}

Graph &Graph::operator=(const Graph &other) {
    num_edges = num_vertices = 0;

    delete[](vertex_adj_lists);

    num_edges = other.num_edges;
    num_vertices = other.num_vertices;
    vertex_adj_lists = new LinkedList<int>[num_vertices];
    for(int i = 0; i < num_vertices; i++) {
        vertex_adj_lists[i] = other.vertex_adj_lists[i];
    }

    return *this;
}

LinkedList<LinkedList<int> *> *Graph::GedPathsList() {
    LinkedList<LinkedList<int> *> *paths = new LinkedList<LinkedList<int> *>;
    for(int i = 0;  i < num_vertices; i++) {
        bool *checked = new bool[num_vertices]();
//        LinkedList<int> *paths_for_crt = TraverseComponent(&LinkedList<int>::pushBack, checked, i);
        paths->pushBack(TraverseComponent(&LinkedList<int>::pushBack, checked, i));
        delete(checked);
    }
    return paths;
}

int getVerticesNumber(Graph &g) {
    return g.num_vertices;
}

