#include <iostream>

using namespace std;

class Base {
public:
    Base() {
        cout<<"Baza"<<endl;
    }
    Base(int a) {
        cout<<"Baza "<<a<<endl;
    }
};

class Der : public Base {
public:
    Der() {
        Base(7);
    }

    Der(int a) : Base(a) {
    }
};


int main() {

    Der a;

    return 0;
}