#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct element {
    int e;
    double w;
};

void swap(element &a, element &b) {
    if (&a == &b) return;
    element tmp = a;
    a = b;
    b = tmp;
}

int partition(vector<element> & a, int l, int r) {
    int i = l + 1;
    int piv = a[l].e;
    for (int j = l + 1; j <= r; j++) {
        if (a[j].e < piv) {
            swap(a[i], a[j]);
            i += 1;
        }
    }
    swap(a[l], a[i - 1]);
    return i - 1;
}

void kthSmallest(vector<element> &a, int l, int r, int k) {
    int pos = partition(a, l, r);
    if (pos - l == k - 1)
        return;
    if (pos - l > k - 1) {
        kthSmallest(a, l, pos - 1, k);
        return;
    }
    kthSmallest(a, pos + 1, r, k - (pos - l + 1));
}

ostream & operator<<(ostream & o, element e) {
    o<<e.e<<" "<<e.w<<endl;
    return o;
}


element findWeightedMedian(vector<element> & a, int l, int r) {
    if (r - l == 0) {
        return a[l];
    }
    if (r - l == 1) {
        if (a[l].w >= a[r].w)
            return a[l];
        else
            return a[r];
    }

    int p = (r - l) / 2 + 1;
    kthSmallest(a, l, r, p);

    int piv = p + l - 1;

    double w_low = 0, w_high = 0;
    for (int i = l; i < piv; i++) {
        w_low += a[i].w;
    }
    for (int i = piv + 1; i <= r; i++) {
        w_high += a[i].w;
    }

    if (w_low < 0.5 && w_high <= 0.5) {
        return a[piv];
    }
    else if (w_low >= 0.5) {
        a[piv].w += w_high;
        return findWeightedMedian(a, l, piv);
    } else {
        a[piv].w += w_low;
        return findWeightedMedian(a, piv, r);
    }
}


int main() {
    vector<element> in = {{5, 0.1}, {1, 0.12}, {3, 0.05}, {2, 0.1}, {9, 0.2}, {6, 0.13}, {11, 0.3}};

    element e = findWeightedMedian(in, 0, in.size() - 1);

    cout<<e.e<<endl;


    for (auto x : in) {
        cout<<x.e<<" "<<x.w<<endl;
    }

    return 0;
}