//https://csacademy.com/contest/round-13/#task/dominant-point
#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

int main()
{
    fstream f;
    f.open("input.in", ios::in);

    short int n;

    f>>n;

    int points[2][n+1] = {
       {INT_MIN},
       {INT_MIN}
    };

    for(int i = 1; i <= n; i++)
    {
        f>>points[0][i]>>points[1][i];
        if(points[0][0] < points[0][i])
            points[0][0] = points[0][i];
        if(points[1][0] < points[1][i])
            points[1][0] = points[1][i];
    }

    f.close();

    int domInd = -1;

    for(int i = 1; i <= n; i++)
        if(points[0][0] == points[0][i] && points[1][0] == points[1][i])
        {
            domInd = i;
            break;
        }

    cout<<points[0][0]<<" "<<points[1][0];

    f.open("output.out", ios::out);
    f<<domInd;
    f.close();

    return 0;
}
