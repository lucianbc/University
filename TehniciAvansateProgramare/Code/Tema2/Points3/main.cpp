#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <climits>

using namespace std;

typedef unsigned long long dist_type;

const dist_type MAX_DIST = ULLONG_MAX;

struct point {
    int x;
    int y;

    point(int x, int y) : x(x), y(y) {}

    string toString() {
        stringstream ss;
        ss << "(x: "<<x<<", y: "<<y<<")";
        return ss.str();
    }
};

dist_type distance(point* p1, point* p2) {
    return (dist_type) (p1->x - p2->x) * (p1->x - p2->x) +
            (dist_type) (p1->y - p2->y) * (p1->y - p2->y) ;
}

dist_type naive(vector<point*> pts) {
    if (pts.empty()) return MAX_DIST;
    if (pts.size() ==1) return MAX_DIST;

    auto min_dist = MAX_DIST;

    for (int i = 0; i < pts.size() - 1; i++) {
        for (int j = i + 1; j < pts.size(); j++) {
            dist_type dd = distance(pts[i], pts[j]);
            if (dd < min_dist)
                min_dist = dd;
        }
    }
    return min_dist;
}

dist_type min_strip_distance(vector<point*> strip, long long dist) {
    auto min_dist = MAX_DIST;

    double length = sqrt(dist);

    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && (strip[j]->y - strip[i]->y <= length); j++) {
            dist_type dd = distance(strip[i], strip[j]);
            if (dd < min_dist) {
                min_dist = dd;
            }
        }
    }

    return min_dist;
}

dist_type compute(vector<point*> px, vector<point*> py) {

    if (px.size() <= 3)
        return naive(px);

    point* mid_point = px[px.size() / 2];

    vector<point*> pxL, pxR;

    unordered_map<point*, int> mapSides;

    int side = 1;
    for (auto p : px) {
        if (p->x < mid_point->x) {
            pxL.push_back(p);
            mapSides[p] = -1;
        } else if (p->x == mid_point->x) {
            if (side == -1) {
                pxL.push_back(p);
            } else {
                pxR.push_back(p);
            }
            mapSides[p] = side;
            side *= -1;
        } else {
            pxR.push_back(p);
            mapSides[p] = 1;
        }
    }

    vector<point*> pyL, pyR;
    for (auto p : py) {
        if (mapSides[p] == -1) {
            pyL.push_back(p);
        } else {
            pyR.push_back(p);
        }
    }

    dist_type distL = compute(pxL, pyL);
    dist_type distR = compute(pxR, pyR);

    dist_type d = min(distL, distR);

    vector<point*> strip;

    for (auto p : py) {
        if (abs(p->x - mid_point->x) <= d) {
            strip.push_back(p);
        }
    }

    return min(d, min_strip_distance(strip, d));
}

bool comp_x(point* p1, point* p2) {
    return p1->x < p2->x;
}

bool comp_y(point* p1, point* p2) {
    return p1->y < p2->y;
}

double closest(vector<point*> points) {
    vector<point*> px, py;
    for (auto p : points){
        px.push_back(p);
        py.push_back(p);
    }
    sort(px.begin(), px.end(), comp_x);
    sort(py.begin(), py.end(), comp_y);

    dist_type square_dist = compute(px, py);

    return sqrt(square_dist);
}

vector<point*> read(istream &fin) {
    vector<point*> points;

    int n;
    fin>>n;
    while (n) {
        int x, y;
        fin>>x>>y;
        points.push_back(new point(x, y));
        n--;
    }

    return points;
}

int main() {
    ifstream fin("cmap.in");
    ofstream fout("cmap.out");

    vector<point*> pts = read(fin);

    double d = closest(pts);

    fout<<fixed<<setprecision(6)<<d<<endl;

    fin.close();
    fout.close();

    return 0;
}

