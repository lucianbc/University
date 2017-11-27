/// Programare Procedurala, Tema 2
/// Proiect realizat de Boaca Lucian, grupa 141
/// Tema proiectului: Raportul financiar al unei companii pe o luna

/**
    Cerinta:
    -Sa se realizeze un program care sa simuleze operatiile efectuate asupra unei baze de date.
    -Datele introduse trebuie sa fie persistente de la o rulare a programului la alta.
    -Programul trebuie sa afiseze un meniu care sa faciliteze efectuarea operatiilor de afisare,
    adaugare si stergere a inregistrarilor.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tabele.h"
#include "CRUD.h"
#include "Utilitare.h"

void (*proceduri[14])(void);

void iesire(void)
{
    exit(0);
}

int comp(const void *s1, const void *s2)
{
    Cheltuieli *c1 = s1;
    Cheltuieli *c2 = s2;

    return strcmp(c1->code, c2->code);
}

void initializareFunctii(void)
{
    proceduri[0] = afiseazaAngajati;
    proceduri[1] = adaugaAngajat;
    proceduri[2] = stergeAngajat;

    proceduri[3] = afiseazaCheltuieli;
    proceduri[4] = adaugaCheltuiala;
    proceduri[5] = stergeCheltuiala;

    proceduri[6] = afiseazaVenituri;
    proceduri[7] = adaugaVenit;
    proceduri[8] = stergeVenit;

    proceduri[9] = afiseazaSalariiPermanente;
    proceduri[10] = modificaSalariiPermanente;

    proceduri[11] = afiseazaSalariiFreelance;
    proceduri[12] = modificaSalariiFreelance;

    proceduri[13] = afiseazaRaportGeneral;

    proceduri[14] = iesire;
}

void meniuPrincipal()
{
    int loop = 1;
    do
    {
        clearScreen();
        printf("Meniu principal: \n");
        printf("1.  Afiseaza Angajati\n");
        printf("2.  Adauga Angajat\n");
        printf("3.  Sterge Angajat\n");
        printf("4.  Afiseaza Cheltuieli\n");
        printf("5.  Adauga Cheltuieli\n");
        printf("6.  Sterge Cheltuieli\n");
        printf("7.  Afiseaza Venituri\n");
        printf("8.  Adauga Venituri\n");
        printf("9.  Sterge Venituri\n");
        printf("10. Afiseaza Salariile Angajatilor Permanenti\n");
        printf("11. Modifica Salariile Angajatilor Permanenti\n");
        printf("12. Afiseaza Salariile Angajatilor Temporari\n");
        printf("13. Modifica Salariile Angajatilor Temporari\n");
        printf("14. Afiseaza Raport General\n");
        printf("15. Iesire\n");
        printf("\n\n");

        int opt = -1;

        do
        {
            printf("Introduceti numarul optiunii dorite: ");
            scanf("%d", &opt);
            getchar();
        }
        while(!(opt >= 1 && opt <= 15));

        clearScreen();

        proceduri[opt - 1]();

        printf("\n\n");
        printf("1. Inapoi\n");
        printf("2. Iesire\n\n");
        printf("Introduceti optiunea: ");
        scanf("%d", &loop);
        getchar();
    }
    while(loop == 1);
}

int main()
{
    initializare();
    initializareFunctii();

    qsort(cheltuieli, NUMAR_CHELTUIELI, sizeof(Cheltuieli), comp);

    meniuPrincipal();

    return 0;
}
