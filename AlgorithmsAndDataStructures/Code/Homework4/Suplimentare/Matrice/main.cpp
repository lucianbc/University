#include <iostream>
#include "Matrice.h"

using namespace std;

void test()
{
    Row r1 = newRow();
    addCellToRow(r1, 1, 0);
    addCellToRow(r1, 2, 1);
    addCellToRow(r1, 3, 2);
    addCellToRow(r1, 4, 3);
    addCellToRow(r1, 5, 4);
    addCellToRow(r1, 6, 5);

    //showRow(r1);

    Row r2 = newRow();
    addCellToRow(r2, 2, 0);
    addCellToRow(r2, 4, 1);
    addCellToRow(r2, 6, 2);
    addCellToRow(r2, 8, 3);
    addCellToRow(r2, 10, 4);
    addCellToRow(r2, 12, 5);

    Row r3 = newRow();
    addCellToRow(r3, 99, 0);
    addCellToRow(r3, 93, 1);
    addCellToRow(r3, 19, 2);

    Matrix myMat = newMatrix();
    addRowToMatrix(myMat, &r1, 0);
    addRowToMatrix(myMat, &r2, 1);
    addRowToMatrix(myMat, &r3, 2);

    showMatrix(myMat);
}

void test2()
{
    int NR_ROWS = 6;
    int NR_COLS = 6;

    int a[6][100] = { {0, 0, 1, 2, 3, 0},
                      {1, 2, 3, 4, 5, 6},
                      {0, 0, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 17},
                      {0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0} };

    Matrix mx;

    mx = process2dArray(a, NR_ROWS, NR_COLS);

    //showMatrix(mx);

    showRealMatrix(mx);

    //showRealRow(*(mx.firstRow->thisRow));

}

void test3()
{
    int NR_COLS = 6, NR_ROWS = 6;
    int a[6][100] = { {1, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0},
                      {0, 0, 2, 3, 0, 0},
                      {0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 4} };

    int b[6][100] = { {1, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 2, 0, 0},
                      {0, 0, 0, 3, 0, 0},
                      {0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 4} };

    Matrix m1 = process2dArray(a, NR_ROWS, NR_COLS);
    Matrix m2 = process2dArray(b, NR_ROWS, NR_COLS);

    Matrix sum = addMatrixes(m1, m2);

    showRealMatrix(sum);
}

int main()
{
    test3();

    return 0;
}
