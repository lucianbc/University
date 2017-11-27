//
// Created by lucian on 02-Mar-17.
//

#ifndef TEST_INITIAL_FORMA_H
#define TEST_INITIAL_FORMA_H

#define PI 3.14

#include <iostream>
#include <cmath>

class Forma {

protected:
    float H;

public:
    virtual void citire(std::istream &in, std::ostream &out);
    virtual float getVolum() = 0;
    virtual float getSuprafata() = 0;
    Forma() { H = 0; }
};


class Cilindru : public Forma {

    float R;

    void citire(std::istream &fin, std::ostream &out) override;

    float getVolum() override;

    float getSuprafata() override;

public:
    Cilindru() { R = 0; }
};

class Paralelipiped : public Forma {

    float L, l;

    void citire(std::istream &in, std::ostream &out) override;

    float getVolum() override;

    float getSuprafata() override;

public:
    Paralelipiped() { L = l = 0; }
};

class Patratic : public Forma {
    float L;

    void citire(std::istream &in, std::ostream &out) override;

    float getVolum() override;

    float getSuprafata() override;

public:
    Patratic() { L = 0; }
};

class Prisma : public Forma {
    float C, c;

    void citire(std::istream &in, std::ostream &out) override;

    float getVolum() override;

    float getSuprafata() override;

public:
    Prisma() { C = c = 0; }
};

#endif //TEST_INITIAL_FORMA_H
