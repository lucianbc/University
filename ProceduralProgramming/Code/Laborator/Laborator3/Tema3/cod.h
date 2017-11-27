#ifndef COD_H_INCLUDED
#define COD_H_INCLUDED

typedef struct
{
    char nume[30];
    float nota_mate;
    float nota_info;
    float nota_bac;
    float medie;
    unsigned short int nr_legitimatie;
    unsigned char admis;
    unsigned char buget;
} Candidat;

typedef enum {LISTA_INTREAGA, BUGET, TAXA, RESPINSI} Optiune;

void isUpper(char*);

void expressionEval(char[], int);

void adaugareCandidat(Candidat[], int*);

void repartitieBuget(Candidat[], int);

void afisareCandidati(Candidat[], int, Optiune);

#endif // COD_H_INCLUDED
