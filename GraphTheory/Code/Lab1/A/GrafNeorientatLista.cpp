#include "GrafNeorientatLista.h"

using namespace std;

namespace GrafNeorientatLista
{
    vector<Nod*>* citeste(istream &fin)
    {
        unsigned int n, m;
        fin>>n>>m;
        vector<Nod*> *listaNoduri = new vector<Nod*>(n, nullptr);
        for(int i = 0; i < m; i++)
        {
            int u, v;
            fin>>u>>v;
            u--;
            v--;

            Nod* nod1 = new Nod;
            nod1->val = v;
            nod1->next = (*listaNoduri)[u];
            (*listaNoduri)[u] = nod1;

            Nod* nod2 = new Nod;
            nod2->val = u;
            nod2->next = (*listaNoduri)[v];
            (*listaNoduri)[v] = nod2;
        }
        return listaNoduri;
    }

    void afisare(vector<Nod*> *lista, ostream &out)
    {
        for(int i = 0; i < lista->size(); i++)
        {
            cout<<i+1<<": ";
            Nod* crt = (*lista)[i];
            while (crt)
            {
                cout<<crt->val + 1<<" ";
                crt = crt->next;
            }
            cout<<endl;
        }
    }

    void dezalocare(vector<Nod*> *&vec)
    {
        for(int i = 0; i < vec->size(); i++) {
            Nod *crt = (*vec)[i];
            while (crt) {
                Nod *tmp = crt->next;
                delete crt;
                crt = tmp;
            }
        }

        cout<<"aici ajunge\n";

        vec->clear();

        vec = nullptr;
    }
}
