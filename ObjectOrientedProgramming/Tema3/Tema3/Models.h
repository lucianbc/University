//
// Created by Lucian on 21/05/2017.
//

#ifndef TEMA3_MODELS_H
#define TEMA3_MODELS_H

#include <string>
#include "Vector.h"

using namespace std;

enum class TipFilm { ACTIUNE, COMEDIE, DRAMA };

class Film {

private:
    string nume;
    TipFilm tip;
    int durata;
    Vector<Persoana*, 20> personal;
    double incasareTotala;

public:
    Film(const string &nume, TipFilm tip, int durata);

    const string &getNume() const;

    void setNume(const string &nume);

    TipFilm getTip() const;

    void setTip(TipFilm tip);

    int getDurata() const;

    void setDurata(int durata);
};


class Persoana {

private:
    string cnp;
    string nume;
    double incasare;

protected:
    double castigTotal;

public:
    Persoana(const string &cnp, const string &nume, double incasare);

    const string &getCnp() const;

    void setCnp(const string &cnp);

    const string &getNume() const;

    void setNume(const string &nume);

    double getIncasare() const;

    void setIncasare(double incasare);

    virtual void incaseaza(int incasareFilm);
};


class Actor : public Persoana {
public:
    Actor(const string &cnp, const string &nume, double incasare);
};


class ActorPrincipal : public Actor {

private:
    double incasareBonusProcent;

public:
    ActorPrincipal(const string &cnp, const string &nume, double incasare, double incasareBonusProcent);

    void incaseaza(int incasareFilm) override;
};

class Regizor : public Persoana {
private:
    double castigFix;

public:
    Regizor(const string &cnp, const string &nume, double incasare, double castigFix);

    void incaseaza(int incasareFilm) override;
};

class Cinematograf {
    string nume;
public:
    Cinematograf(const string &nume);
};

class Rulaj {
    Film* film;
    Cinematograf* cinematograf;
    double incasare;

public:
    Rulaj(Film *film, Cinematograf *cinematograf, double incasare);

    Film *getFilm() const;

    void setFilm(Film *film);

    Cinematograf *getCinematograf() const;

    void setCinematograf(Cinematograf *cinematograf);

    double getIncasare() const;

    void setIncasare(double incasare);
};

#endif //TEMA3_MODELS_H
