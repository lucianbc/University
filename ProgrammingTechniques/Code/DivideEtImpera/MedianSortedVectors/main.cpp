#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a > b ? b : a;
}

ostream& operator<<(ostream & o, vector<int> v) {
    for (auto x : v) {
        o<<x<<" ";
    }
    return o;
}

double findMedianSortedArray(vector<int> x, vector<int> y) {
    vector<int> &a = x.size() < y.size() ? x : y;
    vector<int> &b = &a == &x ? y : x;

    int left = 0, right = a.size();
    int aa = a.size(), bb = b.size();


    while (left <= right) {
        int partitionX = (left + right) / 2;
        int partitionY = (aa + bb + 1) / 2 - partitionX;

        int maxLeftX = partitionX == 0 ? INT_MIN : a[partitionX - 1];
        int minRightX = partitionX == aa ? INT_MAX : a[partitionX];

        int maxLeftY = partitionY == 0 ? INT_MIN : b[partitionY - 1];
        int minRightY = partitionY == bb ? INT_MAX : b[partitionY];

        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((aa + bb) % 2 == 0) {
                return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2;
            } else {
                return max(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            right = partitionX - 1;
        } else {
            left = partitionX + 1;
        }
    }

    return -1;
}



int main() {

    vector<int> x = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    vector<int> y = {1, 23, 25};

    double m = findMedianSortedArray(x, y);

    cout<<m<<endl;

    return 0;
}
#pragma clang diagnostic pop