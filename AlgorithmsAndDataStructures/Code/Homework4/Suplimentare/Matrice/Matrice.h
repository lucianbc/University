#ifndef MATRICE_H_INCLUDED
#define MATRICE_H_INCLUDED

#include <cstdio>
#include <iostream>


struct CellNode
{
    int colIndex;
    int val;
    CellNode* nextCell;
};

struct Row
{
    CellNode* firstCell;
    CellNode* lastCell;
    int length;
    int realLength;
};

struct RowNode
{
    int rowIndex;
    RowNode* nextRow;
    Row* thisRow;
};

struct Matrix
{
    RowNode* firstRow;
    RowNode* lastRow;
    int height;
    int realHeight;
};

Row newRow(void);

// This function only adds cells to the back of the row
void addCellToRow(Row&, int, int);

Matrix newMatrix(void);

// This function only adds rows to the end of the matrix
void addRowToMatrix(Matrix&, Row*, int);

void showRow(Row);

void showMatrix(Matrix);

Matrix process2dArray(int[][100], int, int);

void showRealRow(Row);

void showRealMatrix(Matrix);

Matrix addMatrixes(Matrix, Matrix);

#endif // MATRICE_H_INCLUDED
