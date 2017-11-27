#include <iostream>

using namespace std;

class Obiect {
    int val;
public:
    Obiect(int val) : val(val) {}
    void functie(int x) { val = x; }
    int getVal() { return val; }
};

int main() {

    Obiect o1(19);

    void (Obiect::*f_ptr)(int);
    f_ptr = &Obiect::functie;

    Obiect *tmp = &o1;

    (tmp->*f_ptr)(47);

    cout<<o1.getVal()<<endl;

    return 0;
}