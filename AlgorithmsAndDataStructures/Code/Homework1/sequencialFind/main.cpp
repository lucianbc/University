#include <stdio.h>

using namespace std;

int cauta(int v[], int n, int toFind)
{
    for(int i = 0; i < n; i++)
        if(v[i] == toFind)
            return i;
    return -1;
}

int main()
{
    int v[] = {9, 432, 5, -9, 0, 35};
    int n = sizeof(v)/sizeof(v[0]);

    int poz = cauta(v, n, -9);

    if(poz == -1)
        printf("Elementul nu a fost gasit");
    else
        printf("Elementul a fost gasit pe pozitia %d", poz + 1);

    return 0;
}
