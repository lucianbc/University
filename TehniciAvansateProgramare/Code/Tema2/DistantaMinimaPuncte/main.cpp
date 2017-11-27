#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <unordered_map>

using namespace std;

struct Point {
    int x;
    int y;

    Point() = default;

    Point(int x, int y) : x(x), y(y) {}

    double distance(Point* p) {
        return sqrt(
                (this->x - p->x) * (this->x - p->x) +
                (this->y - p->y) * (this->y - p->y))
                ;
    }

    string toString() {
        stringstream ss;
        ss << "(x: "<<x<<", y: "<<y<<")";
        return ss.str();
    }
};

struct Pair {
    Point* p1;
    Point* p2;

    Pair(Point *p1, Point *p2) : p1(p1), p2(p2) {}

    Pair() : p1(nullptr), p2(nullptr) {}

    double distance() {
        return p1->distance(p2);
    }
};

double naive(const vector<Point*> &points, Pair & pair) {
    if (points.empty()) return DBL_MIN;
    if (points.size() == 1) return DBL_MAX;

    pair.p1 = points[0];
    pair.p2 = points[1];

    for (int i = 0; i < points.size() - 1; i++) {
        for (int j = i + 1; j < points.size(); j++) {
            if (points[i]->distance(points[j]) < pair.distance()) {
                pair.p1 = points[i];
                pair.p2 = points[j];
            }
        }
    }
    return pair.distance();
}

vector<Point*> read(istream &fin) {
    vector<Point*> points;

    int n;
    fin>>n;
    while (n) {
        int x, y;
        fin>>x>>y;
        points.push_back(new Point(x, y));
        n--;
    }

    return points;
}

//vector<Point*> read() {
//    vector<Point*> points;
//    points.push_back(new Point(1, 5));
//    points.push_back(new Point(6, 3));
//    points.push_back(new Point(2, 9));
//    points.push_back(new Point(1, 7));
//    points.push_back(new Point(7, 9));
//    points.push_back(new Point(6, 1));
//    points.push_back(new Point(10, 12));
//    points.push_back(new Point(0, 5));
//    points.push_back(new Point(-1, -4));
//    points.push_back(new Point(0, 0));
//    return points;
//}

double minStripDistance(vector<Point*> strip, double dist, Pair & pair) {
    auto min = DBL_MAX;

    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1 ; j < strip.size() && (strip[j]->y - strip[i]->y) < dist; j++) {
            if (strip[i]->distance(strip[j]) < min) {
                min = strip[i]->distance(strip[j]);
                pair.p1 = strip[i];
                pair.p2 = strip[j];
            }
        }
    }

//    cout<<"min in strip: "<<min<<endl;

    return min;
}

// Divide and Conquer utility function
// px and py are vectors of points sorted by the x and y axes
// the pair argument is used to not only get the distance, but also the points from the algorithm
double compute(vector<Point*> px, vector<Point*> py, Pair & pair) {

    double rez;

    // base case
    if (px.size() <= 3) {
        rez = naive(px, pair);
    } else {
        // divide step
        Point* midPoint = px[px.size() / 2];

        unordered_map<Point*, int> mapSides;

        vector<Point*> pxL;
        vector<Point*> pxR;
        int side = -1;
        for (auto p : px) {
            if (p->x < midPoint->x) pxL.push_back(p);
            else if (p->x == midPoint->x) {
                if(side == -1) {
                    pxL.push_back(p);
                    mapSides[p] = -1;
                }
                else {
                    pxR.push_back(p);
                    mapSides[p] = 1;
                }
                side *= -1;
            }
            else pxR.push_back(p);
        }

        vector<Point*> pyL;
        vector<Point*> pyR;
        for (auto p : py) {
            if (p->x < midPoint->x) pyL.push_back(p);
            else if (p->x == midPoint->x) {
                if (mapSides[p] == -1) pyL.push_back(p);
                else pyR.push_back(p);
            }
            else pyR.push_back(p);
        }

        Pair pairL, pairR;
        double distL = compute(pxL, pyL, pairL);
        double distR = compute(pxR, pyR, pairR);

        // Conquer step
        double d;
        if (distL < distR) {
            d = distL; pair.p1 = pairL.p1; pair.p2 = pairL.p2;
        } else {
            d = distR; pair.p1 = pairR.p1; pair.p2 = pairR.p2;
        }

        vector<Point*> strip;
        for (auto p : py) {
            if (abs(p->x - midPoint->x) <= d) {
                strip.push_back(p);
            }
        }

        rez = min(d, minStripDistance(strip, d, pair));
    }

    cout<<"rez in compute: "<<rez<<endl;

    return rez;
}

double closest(vector<Point*> points, Pair& pair) {
    vector<Point*> px, py;
    for (auto p : points){
        px.push_back(p);
        py.push_back(p);
    }

    sort(px.begin(), px.end(), [](Point* p1, Point* p2) -> bool { return p1->x < p2->x; });
    sort(py.begin(), py.end(), [](Point* p1, Point* p2) -> bool { return p1->y < p2->y; });

    return compute(px, py, pair);
}

int main() {

    ifstream fin("cmap.in");
    ofstream fout("cmap.out");

    vector<Point*> pts = read(fin);

    Pair pair(nullptr, nullptr);

    double d = closest(pts, pair);

    fout<<setprecision(6)<<fixed<<d<<endl;

//    for (auto p : pts) {
//        delete p;
//    }

    fin.close();
    fout.close();
    return 0;
}