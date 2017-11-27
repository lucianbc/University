#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    int R, C;

    Point(int R, int C) : R(R), C(C) {}
    Point(){}

    static int getDistance(Point p1, Point p2) {
        return (int) (abs(p1.R - p2.R) + abs(p1.C - p2.C));
    }
};

int main() {
    int m, n;

    vector<Point> points;

    ifstream fin("graf.in");
    fin>>n>>m;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c;
            fin>>c;
            if(c == '1') points.push_back(Point(i + 1, j + 1));
        }
    }

    Point crt;

    while(fin>>crt.R>>crt.C) {
        Point min(-1, -1);
        for(int i = 0; i < points.size(); i++) {
            if( Point::getDistance(crt, points[i]) < Point::getDistance(crt, min) ) {
                min = points[i];
            }
        }
        cout<<Point::getDistance(crt, min)<<" ["<<min.R<<", "<<min.C<<"]\n";
    }

    return 0;
}