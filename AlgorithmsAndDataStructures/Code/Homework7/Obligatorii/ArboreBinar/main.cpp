#include <iostream>
#include <queue>

using namespace std;

struct NodArbore
{
    int info;
    NodArbore* left;
    NodArbore* right;
};

void AdaugaNod(NodArbore* &arbore, int data)
{
    // creez un nou nod
    NodArbore* nod = new NodArbore;
    nod->info = data;
    nod->left = NULL;
    nod->right = NULL;

    // daca arborele dat nu exista, il initializez cu noul nod
    // si opresc functia
    if(arbore == NULL)
    {
        arbore = nod;
        return;
    }

    // gasesc pozitia in care sa inserez noua frunza si o adaug
    queue<NodArbore*> fii;

    bool adaugat = false;

    fii.push(arbore);

    while(fii.size() != 0 && !adaugat)
    {
        NodArbore* crt = fii.front();
        fii.pop();
        if(crt->left == NULL)
        {
            crt->left = nod;
            adaugat = true;
            break;
        }
        fii.push(crt->left);
        if(crt->right == NULL)
        {
            crt->right = nod;
            adaugat = true;
            break;
        }
        fii.push(crt->right);
    }
}

void parcurgeRSD(NodArbore* arbore)
{
    if(arbore == NULL)
        return;
    cout<<arbore->info<<" ";
    parcurgeRSD(arbore->left);
    parcurgeRSD(arbore->right);
}

void parcurgeSRD(NodArbore* arbore)
{
    if(arbore == NULL)
        return;
    parcurgeSRD(arbore->left);
    cout<<arbore->info<<" ";
    parcurgeSRD(arbore->right);
}

void parcurgeSDR(NodArbore* arbore)
{
    if(arbore == NULL)
        return;
    parcurgeSDR(arbore->left);
    parcurgeSDR(arbore->right);
    cout<<arbore->info<<" ";
}
int main()
{
    NodArbore* myTree = NULL;
    parcurgeRSD(myTree);
    AdaugaNod(myTree, 5);
    AdaugaNod(myTree, 7);
    AdaugaNod(myTree, 9);
    AdaugaNod(myTree, 12);
    AdaugaNod(myTree, 14);
    AdaugaNod(myTree, 16);
    AdaugaNod(myTree, 18);
    AdaugaNod(myTree, 20);
    parcurgeRSD(myTree);
    return 0;
}
