#include <iostream>

using namespace std;

int IntCount = 0;

struct Int {
    int x;

    Int(int x) : x(x) { cout<<"construiesc un Int\n"; IntCount++; }

    virtual ~Int() { cout<<"Sterg un Int\n"; IntCount--; }

    friend ostream&operator<<(ostream& out, Int& val) {
        out<<val.x;
        return out;
    }
};

class Obiect {
    Int* val;

public:
    Obiect() : val(new Int(0)) { cout<<"Default constructor\n"; }
    Obiect(int v) : val(new Int(v)) {cout<<"Def constr with parameter\n";}
    // Rule of three
    Obiect(const Obiect &other) : val(other.val) { cout<<"Const Copy constructor\n"; }
    Obiect&operator=(Obiect &other) { cout<<"Copy assignment operator\n"; val = other.val; return *this; }
    ~Obiect() { cout<<"Destructor\n"; }

    // Rule of five addition
    Obiect&operator=(Obiect &&other) { cout<<"Move asignment\n"; val = other.val; return *this; }
    Obiect(Obiect &&other) noexcept : val(other.val) { cout<<"Move constructor\n"; }

    Int *getVal() const {
        return val;
    }

    void setVal(Int *val) {
        Obiect::val = val;
    }
};


int main() {

    Obiect x(17);


    return 0;
}