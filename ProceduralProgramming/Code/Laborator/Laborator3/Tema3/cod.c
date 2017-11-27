#include "cod.h"
#include <string.h>

//1. Se citeṣte un caracter de la tastatură. Să se verifice dacă este literă mare. Dacă da, să se
//transforme în literă mică ṣi să se afiṣeze. Altfel, să se rescrie caracterul tastat.
void isUpper(char *c)
{
    if(*c >= 'A' && *c <= 'Z')
    {
        *c = *c + 'a' - 'A';
    }
    printf("%c\n", *c);
}

//2. Se citesc de la tastatură construcţii de forma „a operator b”, unde a ṣi b sunt numere întregi, iar
//operatorul poate fi „+”, „-”, „*”, „/”, „%”. Să se afiṣeze valoarea expresiei citite. Să se folosească
//instrucţiunea decizională switch în rezolvarea problemei. Pentru cazul în care operatorul este „/”, să
//se verifice dacă împărţitorul este diferit de 0 (în cazul care este 0, se va afiṣa un mesaj
//corespunzător). De asemenea, să se afiṣeze un mesaj corespunzător în cazul în care operatorul nu
//este unul din cei enumeraţi

void expressionEval(char exp[], int n)
{
    char val1[255], val2[255];
    int i = 0, ie = 0; char op;
    while(exp[i] != '+' && exp[i] != '-' && exp[i] != '*' && exp[i] != '/' && exp[i] != '%')
    {
        val1[ie] = exp[i];
        i++;
        ie++;
    }
    op = exp[i];
    i++;
    val1[ie] = '\0';
    ie = 0;
    while(exp[i] != '\0')
    {
        val2[ie] = exp[i];
        i++;
        ie++;
    }
    val2[ie] = '\0';
    int v1 = atoi(val1);
    int v2 = atoi(val2);
    int valEx = 0;
    switch (op)
    {
        case '+':
                valEx = v1 + v2;
                break;
        case '-':
            valEx = v1 - v2;
            break;
        case '*':
            valEx = v1 - v2;
            break;
        case '/':
            valEx = v1 - v2;
            break;
        case '%':
            valEx = v1 % v2;
            break;
    }
    printf("Valoarea expresiei: %d\n", valEx);
}

