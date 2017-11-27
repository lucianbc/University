#ifndef TABELE_H_INCLUDED
#define TABELE_H_INCLUDED

#define NUMAR_NIVELE_SALARII 3

typedef enum { LOW, MEDIUM, HIGH } niveleSalarii;

typedef union {
    int ore;
    char tip[4];
} modPlata;

typedef struct {
    int index;
    char nume[30];
    char ocupatie[30];
    modPlata plata;
    niveleSalarii nivelSalarizare;
} Angajat;

typedef struct {
    char code[35];
    char nume[30];
    int index;
    int data;
    int pret;
} Cheltuieli;

typedef struct {
    char nume[30];
    int index;
    int valoare;
} Venituri;

typedef struct {
    float venituri;
    float cheltuieli;
    float total;
} Raport;

Raport raport;

int SalariiPermanenti[NUMAR_NIVELE_SALARII];
float SalariiFreelance[NUMAR_NIVELE_SALARII];

int NUMAR_ANGAJATI;
int CAPACITATE_ANGAJATI;
Angajat* angajati;

int NUMAR_CHELTUIELI;
int CAPACITATE_CHELTUIELI;
Cheltuieli* cheltuieli;

int NUMAR_VENITURI;
int CAPACITATE_VENITURI;
Venituri* venituri;

void initializare(void);

void afiseazaAngajati(void);
void adaugaAngajat(void);
void stergeAngajat(void);

void afiseazaCheltuieli(void);
void adaugaCheltuiala(void);
void stergeCheltuiala(void);

void afiseazaVenituri(void);
void adaugaVenit(void);
void stergeVenit(void);

void afiseazaSalariiPermanente(void);
void modificaSalariiPermanente(void);

void afiseazaSalariiFreelance(void);
void modificaSalariiFreelance(void);

void calculeazaRaport(void);
void afiseazaRaportGeneral(void);

#endif // TABELE_H_INCLUDED
