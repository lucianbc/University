#ifndef POLINOM_H_INCLUDED
#define POLINOM_H_INCLUDED

struct Monom {
    Monom* next;
    int grad;
    int coeficient;
};

struct Polinom {
    Monom* head;
    Monom* tail;
    int length;
};

Polinom newPol(void);
void showPol(Polinom);
void deletePol(Polinom&);
void insertMonom(Polinom&, int, int);

#endif // POLINOM_H_INCLUDED
