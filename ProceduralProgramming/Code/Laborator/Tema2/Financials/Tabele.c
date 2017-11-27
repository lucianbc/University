#include "Tabele.h"
#include "CRUD.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void initializare(void)
{
    citesteSalariiFreelance();
    citesteSalariiPermanenti();

    Table a = citesteAngajati();
    angajati = a.location;
    CAPACITATE_ANGAJATI = a.capacity;
    NUMAR_ANGAJATI = a.size;

    Table c = citesteCheltuieli();
    cheltuieli = c.location;
    CAPACITATE_CHELTUIELI = c.capacity;
    NUMAR_CHELTUIELI = c.size;

    Table v = citesteVenituri();
    venituri = v.location;
    CAPACITATE_VENITURI = v.capacity;
    NUMAR_VENITURI = v.size;

    calculeazaRaport();
}

void afiseazaSalariiPermanente(void)
{
    printf("Nivelurile de salarizare pentru angajatii permanenti: \n");
    printf("Low: %d pe luna\n", SalariiPermanenti[LOW]);
    printf("Medium: %d pe luna\n", SalariiPermanenti[MEDIUM]);
    printf("High: %d pe luna\n", SalariiPermanenti[HIGH]);
}

void afiseazaSalariiFreelance(void)
{
    printf("Nivelurile de salarizare pentru angajatii permanenti: \n");
    printf("Low: %.2f pe ora\n", SalariiFreelance[LOW]);
    printf("Medium: %.2f pe ora\n", SalariiFreelance[MEDIUM]);
    printf("High: %.2f pe ora\n", SalariiFreelance[HIGH]);
}

void afiseazaAngajati(void)
{
    int i;
    for(i = 0; i < NUMAR_ANGAJATI; i++)
    {
        char tipAngajat[25];
        float suma = 0;

        if(strcmp(angajati[i].plata.tip, "Ful") == 0)
        {
            strcpy(tipAngajat, "Angajat Permanent");
            suma = SalariiPermanenti[angajati[i].nivelSalarizare];
        }
        else
        {
            strcpy(tipAngajat, "Angajat Temporar");
            suma = SalariiFreelance[angajati[i].nivelSalarizare] * angajati[i].plata.ore;
        }

        printf("%3d %20s %20s %20s %5.2f", i, angajati[i].nume, angajati[i].ocupatie, tipAngajat, suma);
        printf("\n");
    }
}

void adaugaAngajat(void)
{
    printf("Sunteti in meniul de adaugare a unui nou angajat: \n");
    if(CAPACITATE_ANGAJATI == NUMAR_ANGAJATI)
    {
        CAPACITATE_ANGAJATI += 10;
        Angajat *tmp;
        if((tmp = realloc(angajati, sizeof(Angajat) * CAPACITATE_ANGAJATI)) != NULL)
        {
            angajati = tmp;
            printf("Realocare reusita. Noua capacitate este %d\n", CAPACITATE_ANGAJATI);
        }
        else
        {
            printf("Realocare nereusita. Se opreste executarea functiei.\n");
            return;
        }
    }

    if(NUMAR_ANGAJATI == 0)
        angajati[NUMAR_ANGAJATI].index = 0;
    else
        angajati[NUMAR_ANGAJATI].index = angajati[NUMAR_ANGAJATI - 1].index + 1;

    printf("Nume angajat: ");
    fgets(angajati[NUMAR_ANGAJATI].nume, 30, stdin);
    strtok(angajati[NUMAR_ANGAJATI].nume, "\n");

    printf("Ocupatie angajat: ");
    fgets(angajati[NUMAR_ANGAJATI].ocupatie, 30, stdin);
    strtok(angajati[NUMAR_ANGAJATI].ocupatie, "\n");

    int opt = 0;
    while(!(opt == 1 || opt == 2))
    {
        printf("Introduceti 1 pentru angajat permanent sau 2 pentru angajat temporar: ");
        scanf("%d", &opt);
    }

    if(opt == 1)
    {
        strcpy(angajati[NUMAR_ANGAJATI].plata.tip, "Ful");
    }
    else if (opt == 2)
    {
        opt = -1;
        while(!(opt > 0 && opt < 170))
        {
            printf("Introduceti numarul de ore lucrate de angajat pe luna: ");
            scanf("%d", &opt);
        }
        angajati[NUMAR_ANGAJATI].plata.ore = opt;
    }

    opt = 0;
    while(!(opt >= 1 && opt <= 3))
    {
        printf("Introduceti nivelul de salarizare al angajatului: \n");
        printf("1 -> Nivel Scazut   2-> Nivel Mediu   3 -> Nivel Ridicat \n");
        scanf("%d", &opt);
    }

    angajati[NUMAR_ANGAJATI].nivelSalarizare = opt;

    NUMAR_ANGAJATI++;

    calculeazaRaport();
    scrieAngajati();
}

void stergeAngajat()
{
    if(NUMAR_ANGAJATI == 0)
    {
        printf("Tabelul angajatilor nu contine elemente\n");
        return;
    }
    afiseazaAngajati();
    int opt = -1;
    while(!(opt >= 0 && opt < NUMAR_ANGAJATI))
    {
        printf("\nIntroduceti numarul angajatului pe care doriti sa il stergeti: ");
        scanf("%d", &opt);
    }
    if(opt != NUMAR_ANGAJATI - 1)
    {
        angajati[opt] = angajati[NUMAR_ANGAJATI - 1];
    }
    NUMAR_ANGAJATI--;
    calculeazaRaport();
    scrieAngajati();
}

void afiseazaCheltuieli(void)
{
    int i;
    for(i = 0; i < NUMAR_CHELTUIELI; i++)
    {
        printf("%d %s %d %d %s\n", i, cheltuieli[i].nume, cheltuieli[i].pret, cheltuieli[i].data, cheltuieli[i].code);
    }
}

void adaugaCheltuiala(void)
{
    printf("Sunteti in meniul de adaugare a unei noi cheltuieli: \n");
    if(CAPACITATE_CHELTUIELI == NUMAR_CHELTUIELI)
    {
        CAPACITATE_CHELTUIELI += 10;
        Cheltuieli *tmp;
        if((tmp = realloc(cheltuieli, sizeof(Cheltuieli) * CAPACITATE_CHELTUIELI)) != NULL)
        {
            cheltuieli = tmp;
            printf("Realocare a cheltuielilor reusita. Noua capacitate este %d\n", CAPACITATE_CHELTUIELI);
        }
        else
        {
            printf("Realocare nereusita. Se opreste executarea functiei!\n");
            return;
        }
    }

    if(NUMAR_CHELTUIELI == 0)
        cheltuieli[NUMAR_CHELTUIELI].index = 0;
    else
        cheltuieli[NUMAR_CHELTUIELI].index = cheltuieli[NUMAR_CHELTUIELI - 1].index + 1;

    printf("Nume: ");
    fgets(cheltuieli[NUMAR_CHELTUIELI].nume, 30, stdin);
    strtok(cheltuieli[NUMAR_CHELTUIELI].nume, "\n");

    cheltuieli[NUMAR_CHELTUIELI].pret = -1;
    while(cheltuieli[NUMAR_CHELTUIELI].pret <= 0)
    {
        printf("Pret: ");
        scanf("%d", &cheltuieli[NUMAR_CHELTUIELI].pret);
    }

    cheltuieli[NUMAR_CHELTUIELI].data = -1;
    while(!(cheltuieli[NUMAR_CHELTUIELI].data >= 1 && cheltuieli[NUMAR_CHELTUIELI].data <= 31))
    {
        printf("Ziua din luna: ");
        scanf("%d", &cheltuieli[NUMAR_CHELTUIELI].data);
    }

    sprintf(cheltuieli[NUMAR_CHELTUIELI].code, "%d%d", cheltuieli[NUMAR_CHELTUIELI].pret, cheltuieli[NUMAR_CHELTUIELI].data);

    NUMAR_CHELTUIELI++;

    calculeazaRaport();
    scrieCheltuieli();
}

void stergeCheltuiala(void)
{
    if(NUMAR_CHELTUIELI == 0)
    {
        printf("Tabelul cheltuielilor nu contine inregistrari!\n");
        return;
    }
    afiseazaCheltuieli();
    int opt = -1;
    while(!(opt >= 0 && opt < NUMAR_CHELTUIELI))
    {
        printf("\nIntroduceti numarul inregistrarii pe care doriti sa o stergeti: ");
        scanf("%d", &opt);
    }

    if(opt != NUMAR_CHELTUIELI - 1)
    {
        cheltuieli[opt] = cheltuieli[NUMAR_CHELTUIELI - 1];
    }

    NUMAR_CHELTUIELI--;
    calculeazaRaport();
    scrieCheltuieli();
}

void afiseazaVenituri(void)
{
    int i;
    for(i = 0; i < NUMAR_VENITURI; i++)
    {
        printf("%d %s %d\n", i, venituri[i].nume, venituri[i].valoare);
    }
}

void adaugaVenit(void)
{
    printf("Sunteti in meniul de adaugare a unui nou venit: \n");
    if(CAPACITATE_VENITURI == NUMAR_VENITURI)
    {
        CAPACITATE_VENITURI += 10;
        Venituri* tmp;
        if((tmp = realloc(venituri, sizeof(Venituri) * CAPACITATE_VENITURI)) != NULL)
        {
            venituri = tmp;
            printf("Realocarea reusita!\n");
        }
        else
        {
            printf("Realocare esuata\n");
            return;
        }
    }

    if(NUMAR_VENITURI == 0)
        venituri[NUMAR_VENITURI].index = 0;
    else
        venituri[NUMAR_VENITURI].index = venituri[NUMAR_VENITURI - 1].index + 1;

    printf("Nume: ");
    fgets(venituri[NUMAR_VENITURI].nume, 30, stdin);
    strtok(venituri[NUMAR_VENITURI].nume, "\n");

    venituri[NUMAR_VENITURI].valoare = -1;
    while(venituri[NUMAR_VENITURI].valoare <= 0)
    {
        printf("Valoare: ");
        scanf("%d", &venituri[NUMAR_VENITURI].valoare);
    }

    NUMAR_VENITURI++;
    calculeazaRaport();
    scrieVenituri();
}

void stergeVenit(void)
{
    if(NUMAR_VENITURI == 0)
    {
        printf("Tabelul veniturilor nu contine inregistrari.\n");
        return;
    }
    afiseazaVenituri();
    int opt;
    do
    {
        printf("\nIntroduceti numarul inregistrarii pe care doriti sa o stergeti:");
        scanf("%d", &opt);
    }
    while(!(opt >= 0 && opt < NUMAR_VENITURI));

    if(opt != NUMAR_VENITURI - 1)
    {
        venituri[opt] = venituri[NUMAR_VENITURI - 1];
    }

    NUMAR_VENITURI--;
    calculeazaRaport();
    scrieVenituri();
}

void calculeazaRaport()
{
    //printf("Calculez...\n");
    raport.cheltuieli = 0;
    raport.venituri = 0;
    int i;
    for(i = 0; i < NUMAR_ANGAJATI; i++)
    {
        float crtSal = 0;
        if(strcmp(angajati[i].plata.tip, "Ful") == 0)
            crtSal += SalariiPermanenti[angajati[i].nivelSalarizare];
        else
            crtSal += SalariiFreelance[angajati[i].nivelSalarizare] * angajati[i].plata.ore;
        raport.cheltuieli += crtSal;
        //printf("cheltuieli curente: %.2f\n", raport.cheltuieli);
    }
    for(int i = 0; i < NUMAR_CHELTUIELI; i++)
    {
        raport.cheltuieli += cheltuieli[i].pret;
    }

    for(int i = 0; i < NUMAR_VENITURI; i++)
    {
        raport.venituri += venituri[i].valoare;
    }

    raport.total = raport.venituri - raport.cheltuieli;
}

void modificaSalariiFreelance(void)
{
    printf("Sunteti in meniul de modificare a salariilor pentru angajatii de tip freelance.\n");
    printf("Nivelul Low: ");
    scanf("%f", &SalariiFreelance[LOW]);
    printf("Nivelul Medium: ");
    scanf("%f", &SalariiFreelance[MEDIUM]);
    printf("Nivelul High: ");
    scanf("%f", &SalariiFreelance[HIGH]);
    scrieSalariiFreelance();
    printf("Modificarile au fost salvate!\n");
}

void modificaSalariiPermanente(void)
{
    printf("Sunteti in meniul de modificare a salariilor pentru angajatii permanenti.\n");
    printf("Nivelul Low: ");
    scanf("%d", &SalariiPermanenti[LOW]);
    printf("Nivelul Medium: ");
    scanf("%d", &SalariiPermanenti[MEDIUM]);
    printf("Nivelul High: ");
    scanf("%d", &SalariiPermanenti[HIGH]);
    scrieSalariiPermanente();
    printf("Modificarile au fost salvate!\n");
}

void afiseazaRaportGeneral(void)
{
    printf("%30s: %10.2f\n", "Venituri", raport.venituri);
    printf("%30s: %10.2f\n", "Cheltuieli", raport.cheltuieli);
    printf("%30s: %10.2f\n", "Total", raport.total);

}
