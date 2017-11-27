#include "Matrice.h"

using namespace std;

Row newRow()
{
    Row cRow;
    cRow.firstCell = NULL;
    cRow.lastCell = NULL;
    cRow.length = 0;

    return cRow;
}

Matrix newMatrix()
{
    Matrix cMat;
    cMat.firstRow = NULL;
    cMat.lastRow = NULL;
    cMat.height = 0;

    return cMat;
}

void addCellToRow(Row& myRow, int val, int index)
{
    CellNode* newCell = new CellNode;
    newCell->val = val;
    newCell->colIndex = index;
    newCell->nextCell = NULL;

    if(myRow.firstCell == NULL)
    {
        myRow.firstCell = newCell;
        myRow.lastCell = newCell;
    }
    else
    {
        myRow.lastCell->nextCell = newCell;
        myRow.lastCell = newCell;
    }
    myRow.length++;
}

void addRowToMatrix(Matrix& myMatrix, Row* myRow, int index)
{
    RowNode* rowNode = new RowNode;
    rowNode->nextRow = NULL;
    rowNode->rowIndex = index;
    rowNode->thisRow = myRow;

    if(myMatrix.firstRow == NULL)
    {
        myMatrix.firstRow = rowNode;
        myMatrix.lastRow = rowNode;
    }
    else
    {
        myMatrix.lastRow->nextRow = rowNode;
        myMatrix.lastRow = rowNode;
    }
    myMatrix.height++;
}

void showRow(Row myRow)
{
    CellNode* crt = myRow.firstCell;
    while(crt != NULL)
    {
        printf("%d ", crt->val);
        crt = crt->nextCell;
    }
    printf("\n");
}

void showMatrix(Matrix thisMatrix)
{
    RowNode* crtRow = thisMatrix.firstRow;
    while(crtRow != NULL)
    {
        showRow(*(crtRow->thisRow));
        crtRow = crtRow->nextRow;
    }
}

Matrix process2dArray(int a[][100], int rows, int cols)
{
    Matrix myMat = newMatrix();
    myMat.realHeight = rows;
    for(int i = 0; i < rows; i++)
    {
        Row* myPRow = new Row;
        myPRow->realLength = cols;
        myPRow->firstCell = NULL;
        myPRow->lastCell = NULL;
        myPRow->length = 0;
        for(int j = 0; j < cols; j++)
        {
            if(a[i][j] != 0)
                addCellToRow((*myPRow), a[i][j], j);
        }

        if(myPRow->firstCell != NULL)
            addRowToMatrix(myMat, myPRow, i);
    }

    return myMat;
}

void showRealRow(Row myRow)
{
    int lastIndex = 0;
    CellNode* rIt = myRow.firstCell;
    while(rIt != NULL)
    {
        while(lastIndex < rIt->colIndex)
        {
            printf("0 ");
            lastIndex++;
        }
        lastIndex++;
        printf("%d ", rIt->val);
        rIt = rIt->nextCell;
    }
    while(lastIndex < myRow.realLength)
    {
        printf("0 ");
        lastIndex++;
    }
    printf("\n");
}

void showRealMatrix(Matrix myMat)
{
    int lastIndex = 0;
    RowNode* rowIt = myMat.firstRow;
    int cols = rowIt->thisRow->realLength;
    int rows = myMat.realHeight;
    while(rowIt != NULL)
    {
        while(lastIndex < rowIt->rowIndex)
        {
            for(int i = 0; i < cols; i++)
                printf("0 ");
            printf("\n");
            lastIndex++;
        }
        lastIndex++;
        showRealRow(*(rowIt->thisRow));
        rowIt = rowIt->nextRow;
    }

    while(lastIndex < rows)
    {
        for(int i = 0; i < cols; i++)
            printf("0 ");
        printf("\n");
        lastIndex++;
    }
}

Row* addRows(Row r1, Row r2)
{
    Row* sumR = new Row;
    sumR->firstCell = NULL;
    sumR->lastCell = NULL;
    sumR->length = 0;
    sumR->realLength = r1.realLength > r2.realLength ? r1.realLength : r2.realLength;

    CellNode* cit1;
    CellNode* cit2;
    cit1 = r1.firstCell;
    cit2 = r2.firstCell;

    while(cit1 != NULL && cit2 != NULL)
    {
        if(cit1->colIndex == cit2->colIndex)
        {
            addCellToRow((*sumR), cit1->val + cit2->val, cit1->colIndex);
            cit1 = cit1->nextCell;
            cit2 = cit2->nextCell;
        }
        else if(cit1->colIndex < cit2->colIndex)
        {
            addCellToRow((*sumR), cit1->val, cit1->colIndex);
            cit1 = cit1->nextCell;
        }
        else
        {
            addCellToRow((*sumR), cit2->val, cit2->colIndex);
            cit2 = cit2->nextCell;
        }
    }

    CellNode* it = cit1 == NULL ? cit2 : cit1;

    while(it != NULL)
    {
        addCellToRow((*sumR), it->val, it->colIndex);
        it = it->nextCell;
    }
    return sumR;
}

Matrix addMatrixes(Matrix m1, Matrix m2)
{
    Matrix sum = newMatrix();
    sum.realHeight = m1.realHeight > m2.realHeight ? m1.realHeight : m2.realHeight;
    RowNode* it1 = m1.firstRow;
    RowNode* it2 = m2.firstRow;

    while(it1 != it2)
    {
        if(it1->rowIndex == it2->rowIndex)
        {
            Row* sumRow = addRows(*(it1->thisRow), *(it2->thisRow));
            addRowToMatrix(sum, sumRow, it1->rowIndex);
            it1 = it1->nextRow;
            it2 = it2->nextRow;
        }
        else if(it1->rowIndex < it2->rowIndex)
        {
            addRowToMatrix(sum, it1->thisRow, it1->rowIndex);
            it1 = it1->nextRow;
        }
        else
        {
            addRowToMatrix(sum, it2->thisRow, it2->rowIndex);
            it2 = it2->nextRow;
        }
    }

    RowNode* rem = it1 == NULL ? it2 : it1;

    while(rem != NULL)
    {
        addRowToMatrix(sum, rem->thisRow, rem->rowIndex);
        rem = rem->nextRow;
    }

    return sum;
}
