//
// Created by alexis on 07.09.2020.
//

#include "Matrix.h"

Matrix::Matrix() {
    this->matrixArray = nullptr;
    this->sizeRow = this->sizeColumn = 0;
}

Matrix::Matrix(float **array, const int &sizeRow, const int &sizeColumn) {
    if (array == nullptr) {
        this->sizeRow = this->sizeColumn = 0;
        this->matrixArray = nullptr;
        return;
    }
    this->sizeColumn = sizeColumn;
    this->sizeRow = sizeRow;
    this->matrixArray = new float*[this->sizeRow];

    for (int i = 0; i < this->sizeRow; i++) {
        this->matrixArray[i] = new float[this->sizeColumn];
    }

    for (int i = 0; i < this->sizeRow; i++) {
        for (int j = 0; j < this->sizeColumn; j++) {
            this->matrixArray[i][j] = array[i][j];
        }
    }
}


Matrix::Matrix(const int &sizeRow, const int &sizeColumn): sizeColumn(sizeColumn), sizeRow(sizeRow) {
    this->matrixArray = new float*[this->sizeRow];
    for (int i = 0; i < this->sizeRow; i++) {
        this->matrixArray[i] = new float[this->sizeColumn];
    }
}

Matrix::Matrix(const Matrix &original) {
    if (original.matrixArray == nullptr) {
        this->sizeRow = this->sizeColumn = 0;
        this->matrixArray = nullptr;
        return;
    }
    this->sizeRow = original.sizeRow;
    this->sizeColumn = original.sizeColumn;
    this->matrixArray = new float*[this->sizeRow];

    for (int i = 0; i < this->sizeRow; i++) {
        this->matrixArray[i] = new float[this->sizeColumn];
    }

    for (int i = 0; i < this->sizeRow; i++) {
        for (int j = 0; j < this->sizeColumn; j++) {
            this->matrixArray[i][j] = original.matrixArray[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < this->sizeRow; i++) {
        delete [] this->matrixArray[i];
    }

    delete [] this->matrixArray;
}

bool Matrix::isEmpty() {
    if (this->sizeRow == 0 && this->sizeColumn == 0 && this->matrixArray == nullptr) {
        return true;
    }
}

int Matrix::getMatrixColumns() {
    return this->sizeColumn;
}

int Matrix::getMatrixRows() {
    return this->sizeRow;
}

void Matrix::multiplyOnVector(const Vector &vector, const Vector &newVector) {
    if (this->sizeColumn != vector.getVectorSize())  {
        cout << "Matrix and vector sizes don't match" << endl;
        return;
    }
    for (int i=0; i < this->sizeRow; i++) {
        for (int j=0; j < this->sizeColumn; j++) {
            newVector.set(i, newVector.at(i) + this->matrixArray[i][j]*vector.at(j));
        }
    }
}

void Matrix::multiplyOnMatrix(const Matrix &matrix, const Matrix &newMatrix) {
    if (this->sizeColumn != matrix.sizeRow) {
        cout << "Matrices sizes don't match" << endl;
        return;
    }
    for (int k=0; k<matrix.sizeColumn; k++) {
        for (int i=0; i < this->sizeRow; i++) {
            for (int j=0; j < this->sizeColumn; j++) {
                newMatrix.matrixArray[i][k] += this->matrixArray[i][j]*matrix.matrixArray[j][k];
            }
        }
    }
}

void Matrix::printSelf() {
    for (int i = 0; i < this->sizeRow; i++) {
        for (int j = 0; j < this->sizeColumn; j++) {
            cout << this->matrixArray[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::makeDiagonal() {
    for (int i = 0; i < this->sizeRow; i++) {
        float koeff = this->matrixArray[i][i];
        if (koeff != 0) {
            for (int j = 0; j < this->sizeColumn; j++) {
                this->matrixArray[i][j] /= koeff;
            }
        } else {
            this->zerosOnDiagonal = true;
        }
        for (int k = i+1; k < this->sizeRow; k++) {
            float newKoeff = this->matrixArray[k][i];
            if (newKoeff != 0) {
                for (int t = 0; t < this->sizeColumn; t++) {
                    this->matrixArray[k][t] -= newKoeff*matrixArray[i][t];
                }
            }
        }
    }
    this->diagonal = true;
}

void Matrix::removeEmptyRows() {
    int * emptyRowsArray;
    emptyRowsArray = new int [this->sizeRow];
    int emptyRowsNumber = 0;
    for (int i=0; i < this->sizeRow; i++) {
        bool zero = true;
        for (int j = 0; j < this->sizeColumn; j++) {
            if (this->matrixArray[i][j] != 0) {
                zero = false;
                break;
            }
        }
        if (zero) {
            emptyRowsNumber++;
            emptyRowsArray[emptyRowsNumber-1] = i;
        }
    }
    if (emptyRowsNumber != 0) {
        float ** newMatrix;
        newMatrix = new float*[this->sizeRow-emptyRowsNumber];

        for (int i = 0; i < this->sizeRow-emptyRowsNumber; i++) {
            newMatrix[i] = new float[this->sizeColumn];
        }
        int k = 0;
        for (int i = 0; i < this->sizeRow; i++) {
            if (k < emptyRowsNumber) {
                if (i == emptyRowsArray[k]) {
                    k++;
                    continue;
                }
            }
            for (int j = 0; j < this->sizeColumn; j++) {
                newMatrix[i-k][j] = this->matrixArray[i][j];
            }
        }
        this->sizeRow-=emptyRowsNumber;
        delete [] this->matrixArray;
        this->matrixArray = newMatrix;
    }
}

bool Matrix::isDiagonal() {
    return this->diagonal;
}

bool Matrix::hasZerosOnDiagonal() {
    return this->zerosOnDiagonal;
}

float * Matrix::getLine(int i) {
    return this->matrixArray[i];
}

float Matrix::at(int row, int column) {
    return this->matrixArray[row][column];
}
