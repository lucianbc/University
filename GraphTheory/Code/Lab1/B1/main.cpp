#include <iostream>
#include <fstream>
#include <stack>
#include "UndirectedGraph.h"

using namespace std;

int main() {

    ifstream in("graf.in");

    UndirectedGraph myG;

    myG.read(in);

    //myG.print(cout);

    vector<int> controlPoints = {8, 7, 0};

    stack<int> path = myG.getPath(0, controlPoints);

    while (path.size()) {
        cout<<path.top() + 1<<" ";
        path.pop();
    }

    return 0;
}