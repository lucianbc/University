#include <iostream>

using namespace std;

struct number {
    int i;

    explicit number(int i) : i(i) {}

    int operator() (){ return i; }
};

struct nod {
    int n;
    nod * left;
    nod * right;
};


int i = -1;

nod* build(number* v[], int size) {
    i++;
    if (i >= size) return nullptr;
    if (v[i] == nullptr) return nullptr;
    auto * crtNod = new nod;
    crtNod->n = (*v[i])();
    crtNod->left = build(v, size);
    crtNod->right = build(v, size);
    return crtNod;
}


bool parc(nod * crt) {
    if (crt == nullptr)
        return true;
//    cout << crt->n<<" ";
    return  (crt->left == nullptr || crt->left->n <= crt->n) &&
            (crt->right == nullptr || crt->right->n >= crt->n) &&
            parc(crt->left) && parc(crt->right);
}


int main() {

    number * v[] = {new number(4), new number(1), nullptr, new number(3), nullptr, nullptr, new number(7), new number(6), nullptr, nullptr, nullptr };

    nod* arb = build(v, 11);

    cout<<parc(arb);


    return 0;
}