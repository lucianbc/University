#include "cod.h"
#include <stdio.h>
#include <string.h>

#define media_admitere(admitere, bac) (4 * admitere + bac)/5

#define ADMITERE_MIN 5
#define BUGET_PROCENT (75/100)
//3. a) Să se construiască o structură ce conține următoarele date despre candidații la admitere:
//nr_legitimatie, nume, nota_mate, nota_info, nota_bac, medie, admis (Y/N), buget (Y/N).
//b) Sa se defineasca o macroinstrucțiune ce calculează media de admitere dupa regula: 80% media la
//examen, 20% media de bac.
//c) Sa se defineasca o constanta pentru pragul minim de promovabilitate egala cu 5.
//d) Sa se scrie o functie care citeste datele unui candidat, in afara de medie, admis si buget, si le
//adauga unui vector al tuturor candidatilor, pastrand ordinea alfabetica. Media si promovabilitatea
//vor fi calculate folosind definitiile de la punctele b) si c). Numarul de candidati este citit de la
//tastatura.
// se va folosi functia strcmp(s1,s2) ce returneaza un numar:
//o negativ, daca s1 este mai mic decat s2 dpdv al continutului;
//o zero, daca s1 este identic cu s2;
//o pozitiv, daca s1 este mai mare decat s2 dpdv al continutului.
//e). Sa se scrie o functie care completeaza campul „buget” cu Y sau N dupa regula: primii 75%
//(rotunjit in jos) dintre candidatii admisi, in ordinea mediilor, sunt la buget (Y), restul la taxa (N) sau
//nu au promovat examenul de admitere (lasati campul gol).
//f) Sa se scrie o functie care afiseaza datele candidatilor in functie de optiunea aleasa: toti candidatii
//(alfabetic), cei admisi la buget, cei admisi la taxa, cei respinsi (ordonati descrescator dupa medie).
//(meniu cu switch)

Candidat getCandidat()
{
    Candidat c1;
    printf("Introduceti numele candidatului:\n");
    fgets(c1.nume, 30, stdin);
    strtok(c1.nume, "\n");
    printf("Introduceti numarul de legitimatie al candidatului:\n");
    scanf("%hd", &c1.nr_legitimatie);
    printf("Introduceti nota candidatului la matematica:\n");
    scanf("%f", &c1.nota_mate);
    printf("Introduceti nota candidatului la informatica:\n");
    scanf("%f", &c1.nota_info);
    printf("Introduceti nota candidatului la bacalaureat:\n");
    scanf("%f", &c1.nota_bac); getchar();

    c1.medie = media_admitere((c1.nota_info + c1.nota_mate)/2, c1.nota_bac);
    c1.admis = c1.medie > ADMITERE_MIN ? 'Y' : 'N';

    return c1;
}

void adaugareCandidat(Candidat candidati[], int* lg)
{
    Candidat c = getCandidat();

    int poz = *lg;

    (*lg)++;

    while(poz - 1 >= 0 && strcmp(candidati[poz-1].nume, c.nume) > 0)
    {
        candidati[poz] = candidati[poz-1];
        poz--;
    }
    candidati[poz] = c;
}

void repartitieBuget(Candidat candidati[], int n)
{
    int nrB = BUGET_PROCENT * n;
    int i;
    for(i = 0; i < n; i++)
    {
        candidati[i].buget = i < nrB ? 'Y' : 'N';
    }
}

void afisareCandidati(Candidat candidati[], int n, Optiune opt)
{
    int i;
    switch(opt)
    {
        case LISTA_INTREAGA:
            for(i = 0; i < n; i++)
            {
                afisareCandidat(candidati[i]);
//                printf("Nume: %s\n", candidati[i].nume);
//                printf("Nr. Leg: %d\n", candidati[i].nr_legitimatie);
//                printf("Info: %.2f\n", candidati[i].nota_info);
//                printf("Mate: %.2f\n", candidati[i].nota_mate);
//                printf("Bac: %.2f\n", candidati[i].nota_bac);
//                printf("Medie: %.2f\n", candidati[i].medie);
//                printf("Admis: %c\n", candidati[i].admis);
//                printf("Buget: %c\n", candidati[i].buget);
//                printf("\n");
            }
            break;
        case BUGET:
            for(i = 0; candidati[i].buget == 'Y'; i++)
            {
                afisareCandidat(candidati[i]);
//                printf("Nume: %s\n", candidati[i].nume);
//                printf("Nr. Leg: %d\n", candidati[i].nr_legitimatie);
//                printf("Info: %.2f\n", candidati[i].nota_info);
//                printf("Mate: %.2f\n", candidati[i].nota_mate);
//                printf("Bac: %.2f\n", candidati[i].nota_bac);
//                printf("Medie: %.2f\n", candidati[i].medie);
//                printf("\n");
            }
            break;
        case TAXA:
            for(i = BUGET_PROCENT * n ; i < n; i++)
            {
                afisareCandidat(candidati[i]);
//                    printf("Nume: %s\n", candidati[i].nume);
//                    printf("Nr. Leg: %d\n", candidati[i].nr_legitimatie);
//                    printf("Info: %.2f\n", candidati[i].nota_info);
//                    printf("Mate: %.2f\n", candidati[i].nota_mate);
//                    printf("Bac: %.2f\n", candidati[i].nota_bac);
//                    printf("Medie: %.2f\n", candidati[i].medie);
//                    printf("Admis: %c\n", candidati[i].admis);
//                    printf("Buget: %c\n", candidati[i].buget);
//                    printf("\n");
            }
            break;
        case RESPINSI:
            for(i = n - 1; candidati[i].admis == 'N'; i--)
                afisareCandidat(candidati[i]);
            break;
    }
}

void afisareCandidat(Candidat c)
{
    printf("Nume: %s\n", c.nume);
    printf("Nr. Leg: %d\n", c.nr_legitimatie);
    printf("Info: %.2f\n", c.nota_info);
    printf("Mate: %.2f\n", c.nota_mate);
    printf("Bac: %.2f\n", c.nota_bac);
    printf("Medie: %.2f\n", c.medie);
    printf("Admis: %c\n", c.admis);
    printf("Buget: %c\n", c.buget);
    printf("\n");
}
