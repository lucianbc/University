#include <iostream>
#include <fstream>

using namespace std;

int nrNoduri;
int n;
int Noduri[101];

void rezolvare()
{
    fstream f;
    f.open("graf.in", ios::in);
    f>>nrNoduri;
    f>>n;

    int componenteCurenta = 1;
    int n1, n2;

    while(f>>n1>>n2)
    {
        // creez o noua componenta
        if(Noduri[n1] == 0 && Noduri[n2] == 0)
            Noduri[n1] = Noduri[n2] = componenteCurenta++;

        // adaug la o componenta curenta
        if(Noduri[n1] == 0 && Noduri[n2] != 0)
            Noduri[n1] = Noduri[n2];
        else if(Noduri[n2] == 0 && Noduri[n1] != 0)
            Noduri[n2] = Noduri[n1];

        // unesc doua componente
        if(Noduri[n1] != 0 && Noduri[n2] != 0 && Noduri[n1] != Noduri[n2])
        {
            int minComp = min(Noduri[n1], Noduri[n2]);
            int maxComp = Noduri[n1] + Noduri[n2] - minComp;
            for(int i = 0; i < n; i++)
                if(Noduri[i] == maxComp)
                    Noduri[i] = minComp;
                else if(Noduri[i] > maxComp)
                    Noduri[i]--;
            if(componenteCurenta > maxComp)
                componenteCurenta--;
        }
    }


    for(int i = 1; i <= nrNoduri; i++)
    {
        if(Noduri[i] == 0)
            Noduri[i] = componenteCurenta++;
        cout<<Noduri[i]<<" ";
    }
}

int main()
{
    rezolvare();
    return 0;
}
