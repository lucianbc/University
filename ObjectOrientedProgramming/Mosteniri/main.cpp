#include <iostream>

using namespace std;

class Base {

public:
    virtual void afisare(int a) {
        cout<<a<<endl;
    }

    virtual void altaFunctie(int a) {
        cout<<"alta functie: "<<a<<endl;
    }
};

class Derived : public Base {
    void afisare(int a) override {
        cout<<"Derivata: "<<a<<endl;
    }

    void altaFunctie(int a) {
        cout<<"Derivata: "<<a<<endl;
    }
};

int main() {

    Base* myBase = new Derived;

    myBase->afisare(5);
    myBase->altaFunctie(5);

    return 0;
}