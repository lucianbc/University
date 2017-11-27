#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct file {
    int length;
    int index;
};

vector<file*> read(istream &in, unsigned int &p) {
    unsigned int n;
    in>>n>>p;
    vector<file*> files(n);
    for (int i = 0; i < files.size(); i++) {
        auto *f = new file;
        in>>f->length;
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

int main() {
    ifstream fin("date.in");

    unsigned int p;

    vector<file*> files = read(fin, p);

    sort(files.begin(), files.end(), [](file* f1, file* f2) -> bool { return f1->length < f2->length; });

    vector<vector<file*>> tracks(p);

    for (int i = 0; i < files.size(); i++) {
        tracks[i % p].push_back(files[i]);
    }

    for (int i = 0; i < tracks.size(); i++) {
        cout<<"tract "<<i<<": ";
        for (auto &j : tracks[i]) cout<< j->index<<" ";
        cout<<endl;
    }

    free(files);

    return 0;
}