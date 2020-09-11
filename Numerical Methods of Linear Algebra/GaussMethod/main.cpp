#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include <Eigen/Dense>
using namespace std;

int gaussMethod(Matrix system, Vector & answer) {
    system.makeDiagonal();
    if (system.hasZerosOnDiagonal() || system.getMatrixRows() >= system.getMatrixColumns()) {
        system.removeEmptyRows();
    }
    if (system.hasZerosOnDiagonal() || system.getMatrixRows() < system.getMatrixColumns() - 1) {
        cout << "system has no solution" << endl;
        return -1;
    }
    if (system.getMatrixRows() >= system.getMatrixColumns()) {
        cout << "system has more than one solution" << endl;
        return -1;
    }
    for (int i = system.getMatrixRows()-1; i >= 0; i--) {
        Vector answerCopy = Vector(answer);
        Vector row = Vector(system.getLine(i), system.getMatrixColumns()-1);
        answerCopy.multiplyScalar(row, i);
        float elementSum = answerCopy.getElementsSum(i);
        answer.set(i, (system.at(i, system.getMatrixColumns()-1) - elementSum)/system.at(i, i));
    }
    return 0;
}


int firstTest() {
    int sizeFirstVector;
    int sizeSecondVector;

    cout << "Enter size of the first vector" << endl;
    cin >> sizeFirstVector;

    cout << "Enter size of the second vector" << endl;
    cin >> sizeSecondVector;

    float * vectorFirstArray;
    float * vectorSecondArray;


    vectorFirstArray = new float[sizeFirstVector];
    vectorSecondArray = new float[sizeSecondVector];

    cout << "Enter first vector" << endl;

    for (int i = 0; i < sizeFirstVector; i++) {
        cin >> vectorFirstArray[i] ;
    }

    cout << "Enter second vector" << endl;

    for (int i = 0; i < sizeSecondVector; i++) {
        cin >> vectorSecondArray[i] ;
    }

    Vector vectorFirst = Vector(vectorFirstArray, sizeFirstVector);
    Vector vectorSecond = Vector(vectorSecondArray, sizeSecondVector);

    Vector vectorFirstCopy = vectorFirst;
    vectorFirst.multiplyScalar(vectorSecond);
    vectorFirst.printSelf();


    delete [] vectorFirstArray;
    delete [] vectorSecondArray;
    return 0;
}

int secondTest() {
    int sizeFirstRow;
    int sizeFirstColumn;
    int sizeSecondRow;
    int sizeSecondColumn;

    cout << "Enter sizes of first matrix" << endl;
    cin >> sizeFirstRow;
    cin >> sizeFirstColumn;

    cout << "Enter sizes of the second matrix" << endl;
    cin >> sizeSecondRow;
    cin >> sizeSecondColumn;

    float ** matrixFirst;
    float ** matrixSecond;
    float **matrixAnswer;

    matrixFirst = new float*[sizeFirstRow];
    matrixSecond = new float*[sizeSecondRow];
    matrixAnswer = new float*[sizeFirstRow];

    for (int i = 0; i < sizeFirstRow; i++) {
        matrixFirst[i] = new float[sizeFirstColumn];
    }

    for (int i = 0; i < sizeSecondRow; i++) {
        matrixSecond[i] = new float[sizeSecondColumn];
    }
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixAnswer[i] = new float[sizeSecondColumn];
    }
    cout << "Enter first matrix" << endl;
    for (int i = 0; i < sizeFirstRow; i++) {
        for (int j = 0; j < sizeFirstColumn; j++) {
            cin >> matrixFirst[i][j];
        }
    }
    cout << "Enter second matrix" << endl;
    for (int i = 0; i < sizeSecondRow; i++) {
        for (int j = 0; j < sizeSecondColumn; j++) {
            cin >> matrixSecond[i][j];
        }
    }
    Matrix firstMatrix = Matrix(matrixFirst, sizeFirstRow, sizeFirstColumn);
    Matrix secondMatrix = Matrix(matrixSecond, sizeSecondRow, sizeSecondColumn);
    Matrix newMatrix = Matrix(sizeFirstRow, sizeSecondColumn);
    firstMatrix.multiplyOnMatrix(secondMatrix, newMatrix);
    newMatrix.printSelf();

    firstMatrix.makeDiagonal();
    if (firstMatrix.isDiagonal()) {
        firstMatrix.removeEmptyRows();
    }

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixFirst[i];
    }

    delete [] matrixFirst;

    for (int i = 0; i < sizeSecondRow; i++) {
        delete [] matrixSecond[i];
    }

    delete [] matrixSecond;

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixAnswer[i];
    }

    delete [] matrixAnswer;
    return 0;
}

int thirdTest() {
    int sizeFirstRow;
    int sizeFirstColumn;

    cout << "Enter sizes of system matrix" << endl;
    cin >> sizeFirstRow;
    cin >> sizeFirstColumn;


    float ** matrixSystem;
    float ** matrixMain;

    matrixSystem = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixSystem[i] = new float[sizeFirstColumn];
    }

    matrixMain = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixMain[i] = new float[sizeFirstColumn];
    }


    cout << "Enter system matrix" << endl;
    for (int i = 0; i < sizeFirstRow; i++) {
        for (int j = 0; j < sizeFirstColumn; j++) {
            cin >> matrixSystem[i][j];
            if (j != sizeFirstColumn -1) {
                matrixMain[i][j] = matrixSystem[i][j];
            }
        }
    }
    Matrix systemMatrix = Matrix(matrixSystem, sizeFirstRow, sizeFirstColumn);
    Matrix mainMatrix = Matrix(matrixMain, sizeFirstRow, sizeFirstColumn-1);


    Vector answerVector(sizeFirstColumn-1);
    int result = gaussMethod(systemMatrix, answerVector);
    if (result != 0) {
        return -1;
    }

    cout << "The solution is: " << endl;
    answerVector.printSelf();


    Vector controlVector = Vector(sizeFirstRow);
    mainMatrix.multiplyOnVector(answerVector, controlVector);

    cout << "Checking the solution: " << endl;
    controlVector.printSelf();

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixSystem[i];
    }

    delete [] matrixSystem;

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixMain[i];
    }

    delete [] matrixMain;

    return 0;
}

int fourthTest() {
    int sizeFirstRow;
    int sizeFirstColumn;

    cout << "Enter sizes of matrix" << endl;
    cin >> sizeFirstRow;
    cin >> sizeFirstColumn;


    float ** matrixFirst;

    matrixFirst = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixFirst[i] = new float[sizeFirstColumn];
    }


    cout << "Enter matrix" << endl;
    for (int i = 0; i < sizeFirstRow; i++) {
        for (int j = 0; j < sizeFirstColumn; j++) {
            cin >> matrixFirst[i][j];
        }
    }
    Matrix firstMatrix = Matrix(matrixFirst, sizeFirstRow, sizeFirstColumn);


    firstMatrix.makeDiagonal();
    firstMatrix.printSelf();

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixFirst[i];
    }

    delete [] matrixFirst;

    return 0;
}

int fifthTest() {
    Eigen::Matrix4f A;
    Eigen::Vector4f b;
    A << 5, 7, 2, 0, 0, 18, 8, 9, 12, 4, 3, 0, 5, 8, 65, 84;
    b << 5, 58, 1, 3;
    Eigen::Vector4f x = A.completeOrthogonalDecomposition().solve(b);
    cout << "The eigen solution is:\n" << x << endl;
    return 0;
}

int sixthTest() {
    int sizeVector;

    cout << "Enter size of the vector" << endl;
    cin >> sizeVector;

    float * vectorArray;

    vectorArray = new float[sizeVector];

    cout << "Enter vector" << endl;

    for (int i = 0; i < sizeVector; i++) {
        cin >> vectorArray[i] ;
    }

    int sizeMatrixRow;
    int sizeMatrixColumn;

    cout << "Enter sizes of matrix" << endl;
    cin >> sizeMatrixRow;
    cin >> sizeMatrixColumn;

    float ** matrix;

    matrix = new float*[sizeMatrixRow];

    for (int i = 0; i < sizeMatrixColumn; i++) {
        matrix[i] = new float[sizeMatrixColumn];
    }

    cout << "Enter matrix" << endl;

    for (int i = 0; i < sizeMatrixRow; i++) {
        for (int j = 0; j < sizeMatrixColumn; j++) {
            cin >> matrix[i][j];
        }
    }


    Vector vectorFirst = Vector(vectorArray, sizeVector);
    Matrix firstMatrix = Matrix(matrix, sizeMatrixRow, sizeMatrixColumn);

    Vector vectorAnswer = Vector(sizeVector);

    firstMatrix.multiplyOnVector(vectorFirst,vectorAnswer);
    vectorAnswer.printSelf();


    delete [] vectorArray;
    for (int i = 0; i < sizeMatrixRow; i++) {
        delete [] matrix[i];
    }

    delete [] matrix;

    return 0;
}

int main() {
    int result = thirdTest();
    if (result != 0) {
        cout << "Unexpected error during test" << endl;
        return -1;
    }
    result = fifthTest();
    if (result != 0) {
        cout << "Unexpected error during test" << endl;
        return -1;
    }
}