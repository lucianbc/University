#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char key[5];
    char value;
} Pair;

int main()
{
    Pair dictionar[16] = {{"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
                        {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
                        {"1000", '8'}, {"1001", '9'}, {"1010", 'a'}, {"1011", 'b'},
                        {"1100", 'c'}, {"1101", 'd'}, {"1110", 'e'}, {"1111", 'f'} };
    char binNr[64];
    fgets(binNr, 64, stdin);

    int zta = 4 - ((strlen(binNr) - 1) % 4);

    if(zta != 4)
    {
        int i;
        for(i = strlen(binNr) + zta; i >= zta; i--)
        {
            binNr[i] = binNr[i - zta];
        }
        for(i = 0; i < zta; i++)
            binNr[i] = '0';
    }

    int i, j;

    char hexNr[17]; int pc = 0;

    for(i = 0; i < strlen(binNr) - 1; i+=4)
    {
        char part[5];
        for(j = 0; j < 4; j++)
        {
            part[j] = binNr[i + j];
        }
        part[4] = '\0';

        int l = 0, r = 15, poz = -1;

        while(l <= r)
        {
            poz = (l + r) / 2;
            int cmpVal = strcmp(dictionar[poz].key, part);
            if(cmpVal == 0)
                break;
            else if (cmpVal <0)
                l = poz - 1;
            else
                r = poz + 1;
        }
        if(poz != -1)
            hexNr[pc++] = dictionar[poz].value;
    }

    hexNr[pc] = '\0';

    printf("%s", hexNr);

    return 0;
}
