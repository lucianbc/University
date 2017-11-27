#include <iostream>
#include <cstdio>
#include "Queue.h"
#include <climits>

using namespace std;

// 9 3 3 6 9 2 4 7 1 8 5

int main()
{
    int n, k;
    cin>>n>>k;

    Queue coziStocare[k];
    for(int i = 0; i < k; i++)
        coziStocare[i] = newQueue();

    int ok = true;

    for(int i = 0; i < n; i++)
    {
        int vag;
        cin>>vag;

        int minDif = INT_MAX;
        int indexStocare = -1;

        for(int c = 0; c < k; c++)
        {
            int dif = vag - last(coziStocare[c]);
            if(dif >= 0 && dif < minDif)
            {
                minDif = dif;
                indexStocare = c;
            }
        }

        if(indexStocare != -1)
        {
            push(vag, coziStocare[indexStocare]);
            printf("Vagonul %d merge pe linia de stocare numarul %d.\n", vag, indexStocare);
        }
        else
        {
            printf("Vagoanele nu pot fi deplasate astfel incat acestea sa ajunga in ordine.\n");
            ok = false;
            break;
        }
    }

    if(ok)
    {
        do
        {
            ok = false;
            int minIndex = 0;
            for(int c = 0; c < k; c++)
            {
                if(coziStocare[c].length != 0)
                {
                    ok = true;
                    if(peek(coziStocare[c]) < peek(coziStocare[minIndex]))
                        minIndex = c;
                }
            }
            if(ok)
            {
                printf("Vagonul %d trece de pe linia %d pe linia de iesire.\n", peek(coziStocare[minIndex]), minIndex);
                pop(coziStocare[minIndex]);
            }
        } while(ok);
    }

    return 0;
}
