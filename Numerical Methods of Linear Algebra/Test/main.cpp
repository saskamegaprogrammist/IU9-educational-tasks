
#include <iostream>
#include "../Primitives/Matrix.h"
#include "../GaussMethod/LASolver.h"
#include <Eigen/Dense>
#include <random>

#define MAX_MATRIX_VALUE 100


using namespace std;


int multiplyScalarTest() {
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
    cout << vectorFirst.multiplyScalar(vectorSecond) << endl;

    delete [] vectorFirstArray;
    delete [] vectorSecondArray;
    return 0;
}

int matrixMultiplyTest() {
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

    firstMatrix.makeTriangular();
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


int matrixTriangularTest() {
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


    firstMatrix.makeTriangular();
    firstMatrix.printSelf();

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixFirst[i];
    }

    delete [] matrixFirst;

    return 0;
}

int multiplyMatrixOnVectorTest() {
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

    for (int i = 0; i < sizeMatrixRow; i++) {
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

    Vector vectorAnswer = Vector(sizeMatrixRow);

    firstMatrix.multiplyOnVector(vectorFirst,vectorAnswer);
    vectorAnswer.printSelf();


    delete [] vectorArray;
    for (int i = 0; i < sizeMatrixRow; i++) {
        delete [] matrix[i];
    }

    delete [] matrix;

    return 0;
}

int gaussPlainEnterTest() {
    LASolver solver = LASolver();
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
    int result = solver.GaussMethod(systemMatrix, answerVector);
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


int eigenPlainTest() {
    Eigen::Matrix4f A;
    Eigen::Vector4f b;
    A << 5, 7, 2, 0, 0, 18, 8, 9, 12, 4, 3, 0, 5, 8, 65, 84;
    b << 5, 58, 1, 3;
    Eigen::Vector4f x = A.completeOrthogonalDecomposition().solve(b);
    cout << "The eigen solution is:\n" << x << endl;
    return 0;
}

int checkDiagonalDominanceTest() {
    int sizeRow;
    int sizeColumn;

    cout << "Enter sizes of matrix" << endl;
    cin >> sizeRow;
    cin >> sizeColumn;

    float ** matrix;

    matrix = new float*[sizeRow];

    for (int i = 0; i < sizeRow; i++) {
        matrix[i] = new float[sizeColumn];
    }

    cout << "Enter matrix" << endl;
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeColumn; j++) {
            cin >> matrix[i][j];
        }
    }

    Matrix matrixObj = Matrix(matrix, sizeRow, sizeColumn);

    if (matrixObj.isDiagonallyDominant()) {
        cout << "diagonally dominant" << endl;
    } else {
        cout << "not diagonally dominant" << endl;
    }

    for (int i = 0; i < sizeRow; i++) {
        delete [] matrix[i];
    }

    delete [] matrix;

    return 0;
}

int gaussFullRandomTest() {
    LASolver solver = LASolver();
    const int SIZE = 10;
    int sizeFirstRow = SIZE;
    int sizeFirstColumn = SIZE+1;

    float ** matrixSystem;
    float ** matrixMain;

    Eigen::MatrixXf EigenA(SIZE, SIZE);
    Eigen::VectorXf Eigenb(SIZE);

    matrixSystem = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixSystem[i] = new float[sizeFirstColumn];
    }

    matrixMain = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixMain[i] = new float[sizeFirstColumn];
    }

    srand(time(NULL));


    for (int i = 0; i < sizeFirstRow; i++) {
        for (int j = 0; j < sizeFirstColumn; j++) {
            float r = ((float) rand()) / (float) RAND_MAX;
            matrixSystem[i][j] = r * MAX_MATRIX_VALUE;
            if (j != sizeFirstColumn -1) {
                matrixMain[i][j] = matrixSystem[i][j];
                EigenA(i, j) = matrixSystem[i][j];
            } else {
                Eigenb(i) = matrixSystem[i][j];
            }
        }
    }


    Matrix systemMatrix = Matrix(matrixSystem, sizeFirstRow, sizeFirstColumn);
    Matrix mainMatrix = Matrix(matrixMain, sizeFirstRow, sizeFirstColumn-1);

    Vector answerVector(sizeFirstColumn-1);

    systemMatrix.printSelf();

    if (mainMatrix.isDiagonallyDominant()) {
        cout << "diagonally dominant" << endl;
        int result = solver.GaussMethod(systemMatrix, answerVector);
        if (result != 0) {
            return -1;
        }
    } else {
        cout << "not diagonally dominant" << endl;
        int result = solver.GaussMainSelectionRow(systemMatrix, answerVector);
        if (result != 0) {
            return -1;
        }
    }

    cout << "The solution is: " << endl;
    answerVector.printSelf();


    Vector controlVector = Vector(sizeFirstRow);
    mainMatrix.multiplyOnVector(answerVector, controlVector);

    cout << "Checking the solution: " << endl;
    controlVector.printSelf();


    Eigen::VectorXf x = EigenA.completeOrthogonalDecomposition().solve(Eigenb);
    cout << "The eigen solution is:\n" << x << endl;

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


int main() {
    int result = gaussFullRandomTest();
    if (result != 0) {
        cout << "Unexpected error during test" << endl;
        return -1;
    }
}