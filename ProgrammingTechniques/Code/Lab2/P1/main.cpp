#include <iostream>
#include <unordered_map>
#include <fstream>

/*
 * Din fisierul intrare.txt se citeste singura linie de text sa se afiseze fiecare caracter de cate ori apare
 */

using namespace std;

unordered_map<char, int> getCount(string line) {
    unordered_map<char, int> map;

    for (char c : line) {
        map[c] += 1;
    }

    return map;
}

void printCount(const unordered_map<char, int> &charMap) {
    for (auto pair : charMap) {
        cout<<pair.first<<" "<<pair.second<<endl;
    }
}

string read() {
    fstream fin;
    fin.open("intrare.txt", ios::in);
    string line;

    getline(fin, line);

    fin.close();
    return line;
}

int main() {

    string str = read();
    unordered_map<char, int> charCount = getCount(str);
    printCount(charCount);

    return 0;
}