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
    void checkZerosOnDiagonal();
    void swapLines(int rowZero, int columnZero);
public:
    Matrix();
    Matrix(float ** array, const int &sizeRow, const int &sizeColumn);
    Matrix(const int &sizeRow, const int &sizeColumn);
    Matrix(const Matrix &Matrix);
    ~Matrix();
    bool isEmpty();
    int getMatrixColumns();
    int getMatrixRows();
    float * getLine(int i);
    bool isDiagonal();
    bool hasZerosOnDiagonal();
    void multiplyOnVector(const Vector &vector, const Vector &newVector);
    void multiplyOnMatrix(const Matrix &matrix, const Matrix &newMatrix);
    void makeDiagonal();
    void printSelf();
    void removeEmptyRows();
    float at(int row, int column);
};


#endif //GAUSSMETHOD_MATRIX_H
