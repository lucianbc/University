#include <iostream>

#define NHAIDUCI 10
#define MONEDE 50

using namespace std;

void dinamic()
{
    int c = 0;

    int haiduci[NHAIDUCI] = {0};

    for(int i = 0; i < NHAIDUCI; i++)
    {
        for(int j = 0; j < i; j++)
            if(haiduci[j] == 0)
            {
                c++;
                haiduci[j] = 1;
            }
            else
            {
                haiduci[j] = 0;
            }
        haiduci[i] = MONEDE - c;

        c = 0;

        for(int k = 0; k < NHAIDUCI; k++)
            cout<<haiduci[k]<<" ";
        cout<<endl;
    }

    for(int i = 0; i < NHAIDUCI; i++)
        cout<<haiduci[i]<<" ";
}

void liniar()
{
    int c = 0;

    int haiduci[NHAIDUCI] = {0};

    int toGive = 0;

    for(int i = NHAIDUCI - 2; i >= 0; i--)
    {
        haiduci[i] = toGive;
        c += toGive;
        toGive = 1 - toGive;
        cout<<toGive<<endl;
    }

    haiduci[NHAIDUCI - 1] = MONEDE - c;

    for(int i = 0; i < NHAIDUCI; i++)
    {
        cout<<haiduci[i]<<" ";
    }
}

int main()
{
    liniar();

    return 0;
}
