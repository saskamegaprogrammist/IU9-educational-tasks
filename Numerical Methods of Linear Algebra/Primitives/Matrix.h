//
// Created by alexis on 07.09.2020.
//

#ifndef GAUSSMETHOD_MATRIX_H
#define GAUSSMETHOD_MATRIX_H
#include <iostream>
#include "Vector.h"

using namespace std;

class Matrix {
private:
    float ** matrixArray;
    int sizeRow;
    int sizeColumn;
    bool diagonal;
    bool zerosOnDiagonal;
    bool diagonallyDominant;
    bool positive;
    bool symmetrical;
    int *columnsPermutation = nullptr;
    void checkZerosOnDiagonal();
    void checkDiagonallyDominance();
    void checkSymmetrical();
    void checkPositive();
    void swapLinesZero(int rowZero, int columnZero);
    void swapLines(int rowFirst, int rowSecond);
    void swapColumns(int columnFirst, int columnSecond);
    int maxColumnElementRowIndex(int columnIndex, int rowIndexSince);
    int maxRowElementColumnIndex(int rowIndex, int columnIndexSince);
    void makeNullColumn(int diagonalIndex);
public:
    Matrix();
    Matrix(float ** array, const int &sizeRow, const int &sizeColumn);
    Matrix(const int &sizeRow, const int &sizeColumn);
    Matrix(const Matrix &Matrix);
    ~Matrix();
    bool isEmpty();
    int getMatrixColumns() const;
    int getMatrixRows() const;
    float * getLine(int i);
    bool isDiagonal();
    bool hasZerosOnDiagonal();
    void multiplyOnVector(const Vector &vector, const Vector &newVector);
    void multiplyOnMatrix(const Matrix &matrix, const Matrix &newMatrix);
    void makeTriangular();
    void makeTriangularSelectionFull();
    void makeTriangularSelectionColumn();
    void makeTriangularSelectionRow();
    void printSelf();
    void removeEmptyRows();
    bool isDiagonallyDominant();
    bool isSymmetrical();
    bool isPositive();
    float at(int row, int column) const;
    int getIndexPerm(int i);
    float calculateEuclideanNorm();
    float calculateEvenNorm();
    void getInverted2by2(const Matrix &newMatrix);
    float getDeterminant2by2();
    float getConditionNumber2by2();
};


#endif //GAUSSMETHOD_MATRIX_H
