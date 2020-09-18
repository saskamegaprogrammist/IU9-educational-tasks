//
// Created by alexis on 07.09.2020.
//

#include "Matrix.h"
#include "Round.h"

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

    delete [] this->columnsPermutation;

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
            float nV = newVector.at(i) + this->matrixArray[i][j]*vector.at(j);
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

void Matrix::makeNullColumn(int diagonalIndex) {
    float koeff = this->matrixArray[diagonalIndex][diagonalIndex];
    float * normalizedLine;
    normalizedLine = new float [this->sizeColumn];
    if (koeff == 0) {
        this->swapLinesZero(diagonalIndex, diagonalIndex);
        koeff = this->matrixArray[diagonalIndex][diagonalIndex];
        if (koeff == 0) koeff = 1;
    }
    for (int j = 0; j < this->sizeColumn; j++) {
        normalizedLine[j] = this->matrixArray[diagonalIndex][j] / koeff;
    }

    for (int k = diagonalIndex+1; k < this->sizeRow; k++) {
        float newKoeff = this->matrixArray[k][diagonalIndex];
        if (newKoeff != 0) {
            for (int t = 0; t < this->sizeColumn; t++) {
                float newValue = this->matrixArray[k][t] - newKoeff*normalizedLine[t];
                this->matrixArray[k][t] = newValue;
            }
        }
    }
    delete []normalizedLine;
}

void Matrix::makeTriangular() {
    for (int i = 0; i < this->sizeRow; i++) {
        this->makeNullColumn(i);
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
    this->checkZerosOnDiagonal();
    return this->zerosOnDiagonal;
}

float * Matrix::getLine(int i) {
    return this->matrixArray[i];
}

float Matrix::at(int row, int column) {
    return this->matrixArray[row][column];
}

void Matrix::checkZerosOnDiagonal() {
    int minValue = this->sizeColumn;
    if (this->sizeColumn >= this->sizeRow) {
        minValue = this->sizeRow;
    }
    for (int i = 0; i < minValue; i++) {
        if (this->matrixArray[i][i] == 0) {
            this->zerosOnDiagonal = true;
            return;
        }
    }
    this->zerosOnDiagonal = false;
}

void Matrix::swapLines(int rowFirst, int rowSecond) {
    float swap;
    for (int i = 0; i < this->sizeColumn; i++) {
        swap = this->matrixArray[rowSecond][i];
        this->matrixArray[rowSecond][i] =  this->matrixArray[rowFirst][i];
        this->matrixArray[rowFirst][i] = swap;
    }
}

void Matrix::swapLinesZero(int rowZero, int columnZero) {
    int swapLine = rowZero+1;
    for ( ; swapLine < this->sizeRow; swapLine++) {
        if (this->matrixArray[swapLine][columnZero] != 0) break;
    }
    if (swapLine == this->sizeRow) return;
    this->swapLines(rowZero, swapLine);
}

void Matrix::checkDiagonallyDominance() {
    this->diagonallyDominant = false;
    for (int i = 0; i < this->sizeRow; i++) {
        float sum = 0;
        for (int j = 0; j < this->sizeColumn; j++) {
            sum += abs(this->matrixArray[i][j]);
        }
        if (this->matrixArray[i][i] <= sum) return;
    }
    this->diagonallyDominant = true;
}

bool Matrix::isDiagonallyDominant() {
    this->checkDiagonallyDominance();
    return this->diagonallyDominant;
}

int Matrix::maxColumnElementRowIndex(int columnIndex, int rowIndexSince) {
    float max = abs(this->matrixArray[rowIndexSince][columnIndex]);
    int index = rowIndexSince;
    for (int i = rowIndexSince; i < sizeRow; i++) {
        if (abs(this->matrixArray[i][columnIndex]) > max) {
            max = abs(this->matrixArray[i][columnIndex]);
            index = i;
        }
    }
    return index;
}

int Matrix::maxRowElementColumnIndex(int rowIndex, int columnIndexSince) {
    float max = abs(this->matrixArray[rowIndex][columnIndexSince]);
    int index = columnIndexSince;
    for (int i = columnIndexSince; i < sizeColumn-1; i++) {
        if (abs(this->matrixArray[rowIndex][i]) > max) {
            max = abs(this->matrixArray[rowIndex][i]);
            index = i;
        }
    }
    return index;
}

void Matrix::makeTriangularSelectionColumn() {
    for (int i = 0; i < this->sizeRow; i++) {
        int indexMax = this->maxColumnElementRowIndex(i, i);
        if (i != indexMax) this->swapLines(i, indexMax);
        this->makeNullColumn(i);
    }
    this->diagonal = true;
}

void Matrix::swapColumns(int columnFirst, int columnSecond) {
    float swap;
    for (int i = 0; i < this->sizeRow; i++) {
        swap = this->matrixArray[i][columnSecond];
        this->matrixArray[i][columnSecond] =  this->matrixArray[i][columnFirst];
        this->matrixArray[i][columnFirst] = swap;
    }
}

void Matrix::makeTriangularSelectionRow() {
    this->columnsPermutation = new int[this->sizeColumn];
    for (int i = 0; i < this->sizeColumn-1; i++) {
        columnsPermutation[i] = i;
    }
    for (int i = 0; i < this->sizeColumn-1; i++) {
        int indexMax = this->maxRowElementColumnIndex(i, i);
        if (i != indexMax) this->swapColumns(i, indexMax);

        int indOld = this->columnsPermutation[i];
        this->columnsPermutation[i]=this->columnsPermutation[indexMax];
        this->columnsPermutation[indexMax] = indOld;

        this->makeNullColumn(i);
    }
    this->diagonal = true;
}

int Matrix::getIndexPerm(int i) {
    if (!this->columnsPermutation) return i;
    return this->columnsPermutation[i];
}

