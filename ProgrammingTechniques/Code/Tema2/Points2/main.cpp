#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

struct point {
    long long x;
    long long y;

    point(long long x, long long y) : x(x), y(y) {}

    string toString() {
        stringstream ss;
        ss << "(x: "<<x<<", y: "<<y<<")";
        return ss.str();
    }
};

double distance(point* p1, point* p2) {
    long long f1 = (p1->x - p2->x) * (p1->x - p2->x);
    long long f2 = (p1->y - p2->y) * (p1->y - p2->y);

    return sqrt(f1 + f2);
}

double naive(vector<point*> pts) {
    if (pts.empty()) return DBL_MAX;
    if (pts.size() ==1) return DBL_MAX;

    auto min_dist = DBL_MAX;

    for (int i = 0; i < pts.size() - 1; i++) {
        for (int j = i + 1; j < pts.size(); j++) {
            double dd = distance(pts[i], pts[j]);
            if (dd < min_dist)
                min_dist = dd;
        }
    }
    return min_dist;
}

double min_strip_distance(vector<point*> strip, double dist) {
    auto min_dist = DBL_MAX;

    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && (strip[j]->y - strip[i]->y <= dist); j++) {
            double dd = distance(strip[i], strip[j]);
            if (dd < min_dist) {
                min_dist = dd;
            }
        }
    }

    return min_dist;
}

double compute(vector<point*> px, vector<point*> py) {

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

    double distL = compute(pxL, pyL);
    double distR = compute(pxR, pyR);

    double d = min(distL, distR);

    vector<point*> strip;

    for (auto p : py) {
        if (abs(p->x - mid_point->x) <= d) {
            strip.push_back(p);
        }
    }

    return min(d, min_strip_distance(strip, d));
}

double closest(vector<point*> points) {
    vector<point*> px, py;
    for (auto p : points){
        px.push_back(p);
        py.push_back(p);
    }
    sort(px.begin(), px.end(), [](point* p1, point* p2) -> bool { return p1->x < p2->x; });
    sort(py.begin(), py.end(), [](point* p1, point* p2) -> bool { return p1->y < p2->y; });

    return compute(px, py);
}

vector<point*> read(istream &fin) {
    vector<point*> points;

    int n;
    fin>>n;
    while (n) {
        long long x, y;
        fin>>x>>y;
        points.push_back(new point(x, y));
        n--;
    }

    return points;
}


void testOne(const string &filename) {
    string input = filename + ".in";
    string ok = filename + ".ok";

    ifstream fin(input);
    vector<point*> pts = read(fin);
    double d = closest(pts);

    ifstream ok_stream(ok);
    double ok_rez;
    ok_stream>>ok_rez;

    cout<<"ok: "<<ok_rez<<" "<<"my: "<<d<<endl;

    fin.close();
    ok_stream.close();
}

void testAll() {
    string root_name = "grader_test";
    vector<string> files;
    for (int i = 1; i <= 20; i++) {
        files.push_back(root_name + to_string(i));
    }
    for (auto s : files) {
        testOne(s);
    }
}

void rez() {
    ifstream fin("cmap.in");
    ofstream fout("cmap.out");

    vector<point*> pts = read(fin);

    double d = closest(pts);

    fout<<fixed<<setprecision(6)<<d<<endl;

    fin.close();
    fout.close();
}

int main() {
//    rez();

    testAll();

    return 0;
}