//
// Created by lucian on 02-Mar-17.
//

#include "Forme.h"

using namespace std;

void Forma::citire(std::istream &in, std::ostream &out) {
    out<<"Introduceti inaltimea: ";
    in>>this->H;
    //out<<endl;
    in.get();
}

float Cilindru::getVolum() {
    return (float) (PI * R * R * H);
}

float Cilindru::getSuprafata() {
    return (float) (2 * PI * R * H + PI * R * R);
}

void Cilindru::citire(std::istream &in, std::ostream &out) {
    out<<"Introduceti raza: ";
    in>>this->R;
    //out<<endl;
    Forma::citire(in, out);
}

void Paralelipiped::citire(std::istream &in, std::ostream &out) {
    out<<"Introduceti latura mica si latura mare: ";
    in>>this->l>>this->L;
    //out<<endl;
    Forma::citire(in, out);
}

float Paralelipiped::getVolum() {
    return 2 * L * l * H;
}

float Paralelipiped::getSuprafata() {
    return 2 * (l + L) * H + L * l;
}

void Patratic::citire(std::istream &in, std::ostream &out) {
    cout<<"Introduceti latura: ";
    in>>this->L;
    //out<<endl;

    Forma::citire(in, out);
}

float Patratic::getVolum() {
    return L * L * H;
}

float Patratic::getSuprafata() {
    return L * L + 4 * L * H;
}

void Prisma::citire(std::istream &in, std::ostream &out) {
    out<<"Introduceti catetele: ";
    in>>this->c>>this->C;
    //out<<endl;

    Forma::citire(in, out);
}

float Prisma::getVolum() {
    return (c * C  * H) / 2;
}

float Prisma::getSuprafata() {
    return c * C * (1 / 2) + (c + c + sqrt(c * c + C * C)) * H;
}
