//
// Created by Lucian on 21/05/2017.
//

#include "Models.h"

Film::Film(const string &nume, TipFilm tip, int durata) : nume(nume), tip(tip), durata(durata), incasareTotala(0) {}

const string &Film::getNume() const {
    return nume;
}

void Film::setNume(const string &nume) {
    Film::nume = nume;
}

TipFilm Film::getTip() const {
    return tip;
}

void Film::setTip(TipFilm tip) {
    Film::tip = tip;
}

int Film::getDurata() const {
    return durata;
}

void Film::setDurata(int durata) {
    Film::durata = durata;
}

Persoana::Persoana(const string &cnp, const string &nume, double incasare) : cnp(cnp), nume(nume), incasare(incasare) {}

const string &Persoana::getCnp() const {
    return cnp;
}

void Persoana::setCnp(const string &cnp) {
    Persoana::cnp = cnp;
}

const string &Persoana::getNume() const {
    return nume;
}

void Persoana::setNume(const string &nume) {
    Persoana::nume = nume;
}

double Persoana::getIncasare() const {
    return incasare;
}

void Persoana::setIncasare(double incasare) {
    Persoana::incasare = incasare;
}

void Persoana::incaseaza(int incasareFilm) {
    this->castigTotal += (incasare / 100) * incasareFilm;
}

Actor::Actor(const string &cnp, const string &nume, double incasare) : Persoana(cnp, nume, incasare) {}

ActorPrincipal::ActorPrincipal(const string &cnp, const string &nume, double incasare, double incasareBonusProcent)
        : Actor(cnp, nume, incasare), incasareBonusProcent(incasareBonusProcent) {}

void ActorPrincipal::incaseaza(int incasareFilm) {
    Persoana::incaseaza(incasareFilm);

    this->castigTotal += (this->incasareBonusProcent / 100) * incasareFilm;
}

Regizor::Regizor(const string &cnp, const string &nume, double incasare, double castigFix) : Persoana(cnp, nume,
                                                                                                      incasare),
                                                                                             castigFix(castigFix) {}

void Regizor::incaseaza(int incasareFilm) {
    Persoana::incaseaza(incasareFilm);
    this->castigTotal += this->castigFix;
}

Cinematograf::Cinematograf(const string &nume) : nume(nume) {}

Rulaj::Rulaj(Film *film, Cinematograf *cinematograf, double incasare) : film(film), cinematograf(cinematograf),
                                                                        incasare(incasare) {}

Film *Rulaj::getFilm() const {
    return film;
}

void Rulaj::setFilm(Film *film) {
    Rulaj::film = film;
}

Cinematograf *Rulaj::getCinematograf() const {
    return cinematograf;
}

void Rulaj::setCinematograf(Cinematograf *cinematograf) {
    Rulaj::cinematograf = cinematograf;
}

double Rulaj::getIncasare() const {
    return incasare;
}

void Rulaj::setIncasare(double incasare) {
    Rulaj::incasare = incasare;
}
