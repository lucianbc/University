#include <stdio.h>
#include <stdlib.h>

#include "cod.h"

#define MAX_STUDENTI 1000

void test1()
{
    char ch;

    scanf("%c", &ch);

    isUpper(&ch);

    printf("%c\n", ch);
}

void test2()
{
    char ex[] = "5+9";
    int n = strlen(ex);
    expressionEval(ex, n);
}

void test3()
{
    Candidat candidati[MAX_STUDENTI];
    int n = 0;

    int nr;

    scanf("%d", &nr);

    getchar();

    int i;

    for(i = 1; i<=nr; i++)
        adaugareCandidat(candidati, &n);

    repartitieBuget(candidati, n);

    afisareCandidati(candidati, n, LISTA_INTREAGA);

}

int main()
{
    test2();

    return 0;
}
