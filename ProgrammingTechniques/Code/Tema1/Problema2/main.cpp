#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct file {
    int length;
    int times;
    int index;
};

vector<file*> read(istream &in) {
    unsigned long n;
    in>>n;
    vector<file*> files(n);
    for (int i = 0; i < files.size(); i++) {
        auto * f = new file;
        in>>f->length>>f->times;
        f->index = i + 1;
        files[i] = f;
    }

    return files;
}

void free(vector<file*> files) {
    for (auto f : files) {
        delete f;
    }
}

void output(vector<file*> files) {
    for (auto f : files) {
        cout<<f->index<<" ";
    }
    cout<<endl;
}

int time(vector<file*> files, vector<int> perm) {
    int sum = 0;

    for (int i = 0; i < perm.size(); i++) {
        int prevSum = 0;
        for (int j = 0; j <= i; j++) {
            prevSum += files[perm[j]]->length;
        }
        sum += prevSum * files[perm[i]]->times;
    }
    return sum;
}

void checkTimes() {
    ifstream fin("date.in");

    vector<file*> files = read(fin);

    vector<vector<int>> ps = {
            {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}
    };

    for (auto p : ps) {
        cout<<time(files, p)<<endl;
    }

    free(files);
}

int time(vector<file*> files) {
    int sum = 0;

    for (int i = 0; i < files.size(); i++) {
        int prevSum = 0;
        for (int j = 0; j <= i; j++) {
            prevSum += files[j]->length;
        }
        sum += prevSum * files[i]->times;
    }
    return sum;
}

int main() {
    ifstream fin("date.in");

    vector<file*> files = read(fin);

    sort(files.begin(), files.end(), [](file* f1, file* f2) -> bool { return (float)f1->length / f1->times < (float)f2->length / f2->times; });

    cout<<time(files)<<endl;

    output(files);

    free(files);

    return 0;
}