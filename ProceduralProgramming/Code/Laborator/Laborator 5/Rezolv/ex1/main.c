#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//typedef union
//{
//    int balcon;
//    char decomandat;
//    char casa[21];
//} suplimentare;

typedef struct
{
    char adresa[101];
    char tipLocuinta[31];
    int suprafata;
    int numarCamere;
    union
    {
        int balcon;
        char decomandat;
        char casa[21];
    } sup;

} locuinta;

locuinta citesteLocuinta()
{
    locuinta newLoc;
    printf("Tip locuinta: ");
    fgets(newLoc.tipLocuinta, 30, stdin);
}

int main()
{
    char tip[31];
    fgets(tip, 31, stdin);
    int i = 0;
    while(i <= strlen(tip))
    {
        if(tip[i] == '\n')
            printf("Endl_");
        else if (tip[i] == '\0')
            printf("Nullterm_");
        i++;
    }

    //printf("%s", tip);
    //printf("%d\n", strlen(tip));
    //printf("end");
    return 0;
}
