#include "CRUD.h"
#include "Tabele.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

void citesteSalariiPermanenti(void)
{
    FILE *inputFile = NULL;

    if((inputFile = fopen("Database/SalariiPermanent.cdb", "r")) != NULL)
    {
        int i = 0;
        int x;

        while(fscanf(inputFile, "%d", &x) != EOF)
        {
            SalariiPermanenti[i] = x;
            i++;
        }

        fclose(inputFile);

        if(i != NUMAR_NIVELE_SALARII) // testez daca numarul de numere citite este corect
        {
            printf("Date eronate! Se incarca datele predefinite!");
            SalariiPermanenti[LOW] = 1000;
            SalariiPermanenti[MEDIUM] = 2000;
            SalariiPermanenti[HIGH] = 3000;
            scrieSalariiPermanente();
        }
    }
    else
    {
        printf("Fisierul cu salariile angajatilor permanenti nu a fost gasit!\n");
        printf("Initializare cu date predefinite\n");
        SalariiPermanenti[LOW] = 1000;
        SalariiPermanenti[MEDIUM] = 2000;
        SalariiPermanenti[HIGH] = 3000;
        scrieSalariiPermanente();
    }
}

void citesteSalariiFreelance(void)
{
    FILE *inputFile = NULL;

    if((inputFile = fopen("Database/SalariiFreelance.cdb", "r")) != NULL)
    {
        int i = 0;
        float x;

        while(fscanf(inputFile, "%f", &x) != EOF)
        {
            SalariiFreelance[i] = x;
            i++;
        }

        fclose(inputFile);

        if(i != NUMAR_NIVELE_SALARII) // testez daca numarul de numere citite
        {
            printf("Date eronate! Se incarca datele predefinite!");
            SalariiFreelance[LOW] = 1000;
            SalariiFreelance[MEDIUM] = 2000;
            SalariiFreelance[HIGH] = 3000;
            scrieSalariiFreelance();
        }
    }
    else
    {
        printf("Fisierul cu salariile angajatilor temporari nu a fost gasit!\n");
        printf("Initializare cu date predefinite\n");
        SalariiFreelance[LOW] = 1000;
        SalariiFreelance[MEDIUM] = 2000;
        SalariiFreelance[HIGH] = 3000;
        scrieSalariiFreelance();
    }
}

Table citesteAngajati(void)
{
    FILE* inputFile = NULL;

    Table retVal;

    if((inputFile = fopen("Database/Angajati.cdb", "r")) != NULL)
    {
        fscanf(inputFile, "%d", &retVal.size);
        retVal.capacity = retVal.size;
        retVal.location = malloc(retVal.size * sizeof(Angajat));

        Angajat* myTable = retVal.location;

        char buffer[100];
        fgets(buffer, 100, inputFile);

        int i;

        for(i = 0; i < retVal.size; i++)
        {
            char *line = NULL;
            size_t len = 0;
            getline(&line, &len, inputFile);

            char *pStr = strtok(line, " ");
            myTable[i].index = pStr[0] - '0';

            pStr = strtok(NULL, " ");
            strcpy(myTable[i].nume, pStr);

            pStr = strtok(NULL, " ");
            strcpy(myTable[i].ocupatie, pStr);

            pStr = strtok(NULL, " ");
            if(strcmp(pStr, "Ful") == 0)
            {
                strcpy(myTable[i].plata.tip, pStr);
            }
            else
            {
                myTable[i].plata.ore = atoi(pStr);
            }

            pStr = strtok(NULL, " ");

            if(strcmp(pStr, "LOW\n") == 0)
            {
                myTable[i].nivelSalarizare = LOW;
            }
            else if(strcmp(pStr, "MEDIUM\n") == 0)
            {
                myTable[i].nivelSalarizare = MEDIUM;
            }
            else if(strcmp(pStr, "HIGH\n") == 0)
            {
                myTable[i].nivelSalarizare = HIGH;
            }
            else
            {
                // Caz predefinit
                myTable[i].nivelSalarizare = MEDIUM;
            }

            free(line);
        }
        fclose(inputFile);
    }
    else
    {
        printf("Nu a fost gasit tabelul angajatilor. Se creeaza unul predfinit!\n");

        FILE *outputFile = NULL;

        if((outputFile = fopen("Database/Angajati.cdb", "w")) != NULL)
        {
            fprintf(outputFile, "%d", 0);
            fclose(outputFile);
        }
        else
        {
            printf("Eroare la scrierea angajatilor!");
        }
        retVal.capacity = 0;
        retVal.size = 0;
        retVal.location = NULL;
    }

    return retVal;
}

Table citesteCheltuieli(void)
{
    FILE *inputFile = NULL;
    Table retVal;

    if((inputFile = fopen("Database/Cheltuieli.cdb", "r")) != NULL)
    {
        fscanf(inputFile, "%d", &retVal.size);
        retVal.capacity = retVal.size;
        retVal.location = malloc(retVal.size * sizeof(Cheltuieli));

        Cheltuieli* myTable = retVal.location;

        char buffer[100];
        fgets(buffer, 100, inputFile);

        int i;
        for(i = 0; i < retVal.size; i++)
        {
            char *line = NULL;
            size_t len = 0;
            getline(&line, &len, inputFile);

            strcpy(myTable[i].code, "");

            //index
            char *pStr = strtok(line, " ");
            myTable[i].index = pStr[0] - '0';

            //nume
            pStr = strtok(NULL, " ");
            strcpy(myTable[i].nume, pStr);

            //pret
            pStr = strtok(NULL, " ");
            myTable[i].pret = atoi(pStr);
            strcat(myTable[i].code, pStr);

            //data
            pStr = strtok(NULL, " ");
            myTable[i].data = atoi(pStr);
            strcat(myTable[i].code, pStr);

            free(line);
        }
        fclose(inputFile);
    }
    else
    {
        printf("Nu a fost gasit tabelul cheltuielilor. Se creeaza unul cu date predefinite.\n");

        FILE *outputFile = NULL;

        if((outputFile = fopen("Database/Cheltuieli.cdb", "w")) != NULL)
        {
            fprintf(outputFile, "%d", 0);
            fclose(outputFile);
        }
        else
        {
            printf("Eroare la scrierea cheltuielilor!");
        }
        retVal.capacity = 0;
        retVal.size = 0;
        retVal.location = NULL;
    }

    return retVal;
}

Table citesteVenituri(void)
{
    FILE *inputFile = NULL;
    Table retVal;

    if((inputFile = fopen("Database/Venituri.cdb", "r")) != NULL)
    {
        fscanf(inputFile, "%d", &retVal.size);
        retVal.capacity = retVal.size;
        retVal.location = malloc(retVal.size * sizeof(Venituri));

        Venituri *myTable = retVal.location;

        char buffer[100];
        fgets(buffer, 100, inputFile);

        int i;
        for(i = 0; i < retVal.size; i++)
        {
            char *line = NULL;
            size_t len = 0;
            getline(&line, &len, inputFile);

            //index
            char *pStr = strtok(line, " ");
            myTable[i].index = pStr[0] - '0';

            //nume
            pStr = strtok(NULL, " ");
            strcpy(myTable[i].nume, pStr);

            //valoare
            pStr = strtok(NULL, " ");
            myTable[i].valoare = atoi(pStr);

            free(line);
        }
        fclose(inputFile);
    }
    else
    {
        printf("Nu a fost gasit tabelul veniturilor. Se creeaza unul cu date predefinite");

        FILE *outputFile = NULL;

        if((outputFile = fopen("Database/Venituri.cdb", "w")) != NULL)
        {
            fprintf(outputFile, "%d", 0);
            fclose(outputFile);
        }
        else
        {
            printf("Eroare la scrierea veniturilor!");
        }
        retVal.capacity = 0;
        retVal.size = 0;
        retVal.location = NULL;
    }

    return retVal;
}

void scrieAngajati(void)
{
    FILE *outputFile = NULL;

    if((outputFile = fopen("Database/Angajati.cdb", "w")) != NULL)
    {
        fprintf(outputFile, "%d\n", NUMAR_ANGAJATI);
        int i;
        for(i = 0; i < NUMAR_ANGAJATI; i++)
        {
            fprintf(outputFile, "%d %s %s ", angajati[i].index, angajati[i].nume, angajati[i].ocupatie);
            if(strcmp(angajati[i].plata.tip, "Ful") == 0)
                fprintf(outputFile, "%s ", "Ful");
            else
                fprintf(outputFile, "%d ", angajati[i].plata.ore);
            switch(angajati[i].nivelSalarizare)
            {
                case LOW:
                    fprintf(outputFile, "LOW");
                    break;
                case MEDIUM:
                    fprintf(outputFile, "MEDIUM");
                    break;
                case HIGH:
                    fprintf(outputFile, "HIGH");
                    break;
                default:
                    fprintf(outputFile, "MEDIUM");
            }
            fprintf(outputFile, "\n");
        }
        fclose(outputFile);
    }
    else
    {
        printf("Eroare la scrierea angajatilor in fisier.");
    }
}

void scrieCheltuieli(void)
{
    FILE *outputFile = NULL;
    if((outputFile = fopen("Database/Cheltuieli.cdb", "w")) != NULL)
    {
        fprintf(outputFile, "%d\n", NUMAR_CHELTUIELI);
        int i;
        for(i = 0; i < NUMAR_CHELTUIELI; i++)
        {
            fprintf(outputFile, "%d %s %d %d\n", cheltuieli[i].index, cheltuieli[i].nume, cheltuieli[i].pret, cheltuieli[i].data);
        }
        fclose(outputFile);
    }
    else
    {
        printf("Eroare la scrierea cheltuielilor in fisier!\n");
    }
}

void scrieSalariiFreelance(void)
{
    FILE *outputFile = NULL;

    if((outputFile = fopen("Database/SalariiFreelance.cdb", "w")) != NULL)
    {
        int i;
        for(i = 0; i < NUMAR_NIVELE_SALARII; i++)
            fprintf(outputFile, "%.2f ", SalariiFreelance[i]);
        fclose(outputFile);
    }
    else
    {
        printf("Eroare scriere salarii freelance!\n");
    }
}

void scrieSalariiPermanente(void)
{
    FILE *outputFile = NULL;

    if((outputFile = fopen("Database/SalariiPermanent.cdb", "W")) != NULL)
    {
        int i;
        for(i = 0; i < NUMAR_NIVELE_SALARII; i++)
            fprintf(outputFile, "%d ", SalariiPermanenti[i]);
        fclose(outputFile);
    }
    else
    {
        printf("Eroare scriere salarii permanenti!");
    }
}

void scrieVenituri(void)
{
    FILE *outputFile = NULL;
    if((outputFile = fopen("Database/Venituri.cdb", "w")) != NULL)
    {
        fprintf(outputFile, "%d\n", NUMAR_VENITURI);
        int i;
        for(i = 0; i < NUMAR_VENITURI; i++)
        {
            fprintf(outputFile, "%d %s %d\n", venituri[i].index, venituri[i].nume, venituri[i].valoare);
        }
        fclose(outputFile);
    }
    else
    {
        printf("Eroare la scrierea veniturilor in fisier!\n");
    }
}
