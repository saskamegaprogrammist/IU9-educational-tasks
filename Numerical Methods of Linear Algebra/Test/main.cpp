
#include <iostream>
#include "../Primitives/Matrix.h"
#include "../GaussMethod/LASolver.h"
#include "../IterationMethods/JakobiMethod.h"
#include "../IterationMethods/ZeidelMethod.h"
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
    float * vectorMain;

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

    vectorMain = new float[sizeFirstRow];

    srand(time(NULL));


    for (int i = 0; i < sizeFirstRow; i++) {
        for (int j = 0; j < sizeFirstColumn; j++) {
                float r = ((float) rand()) / (float) RAND_MAX;
                matrixSystem[i][j] = r * MAX_MATRIX_VALUE;
            if (j != sizeFirstColumn -1) {
                matrixMain[i][j] = matrixSystem[i][j];
                EigenA(i, j) = matrixSystem[i][j];
            } else {
                vectorMain[i] = matrixSystem[i][j];
                Eigenb(i) = matrixSystem[i][j];
            }
        }
    }


    Matrix systemMatrix = Matrix(matrixSystem, sizeFirstRow, sizeFirstColumn);
    Matrix systemMatrixCopy = Matrix(systemMatrix);
    Matrix mainMatrix = Matrix(matrixMain, sizeFirstRow, sizeFirstColumn-1);
    Vector mainVector = Vector(vectorMain, sizeFirstRow);

    Vector answerVector(sizeFirstColumn-1);
    Vector answerVectorCopy(sizeFirstColumn-1);

    systemMatrix.printSelf();

    if (mainMatrix.isDiagonallyDominant()) {
        cout << "diagonally dominant" << endl;
    } else {
        cout << "not diagonally dominant" << endl;
    }

    int result = solver.GaussMethod(systemMatrix, answerVector);
    if (result != 0) {
        return -1;
    }
    cout << "The simple gauss solution is: " << endl;
    answerVector.printSelf();

    result = solver.GaussMainSelectionFull(systemMatrixCopy, answerVectorCopy);
    if (result != 0) {
        return -1;
    }

    cout << "The hard gauss solution is: " << endl;
    answerVectorCopy.printSelf();

    Eigen::VectorXf x = EigenA.completeOrthogonalDecomposition().solve(Eigenb);
    cout << "The eigen solution is:\n" << x << endl;


    Vector controlVector = Vector(sizeFirstRow);
    mainMatrix.multiplyOnVector(answerVector, controlVector);

    cout << "Checking the simple gauss solution: " << endl;
    controlVector.printSelf();

    Vector controlVectorCopy = Vector(sizeFirstRow);
    mainMatrix.multiplyOnVector(answerVectorCopy, controlVectorCopy);

    cout << "Checking the hard gauss solution: " << endl;
    controlVectorCopy.printSelf();

    Vector mainVectorCopy = Vector(mainVector);
    mainVector.substract(controlVector);

    cout << "Gauss solution inaccuracy: " << endl;
    mainVector.printSelf();

    mainVectorCopy.substract(controlVectorCopy);

    cout << "Gauss hard solution inaccuracy: " << endl;
    mainVectorCopy.printSelf();

    cout << "Gauss solution inaccuracy norm: " << endl;
    cout << mainVector.calculateNorm(2) << endl;

    cout << "Gauss hard solution inaccuracy norm: " << endl;
    cout << mainVectorCopy.calculateNorm(2) << endl;


    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixSystem[i];
    }

    delete [] matrixSystem;

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixMain[i];
    }

    delete [] matrixMain;

    delete [] vectorMain;

    return 0;
}

int perturbationTest() {
    LASolver solver = LASolver();
    const int SIZE = 2;
    int sizeFirstRow = SIZE;
    int sizeFirstColumn = SIZE+1;

    float ** matrixSystem;
    float ** matrixMain;
    float * vectorMain;

    float ** matrixSystemPerturbation;
    float ** matrixMainPerturbation;
    float * vectorMainPerturbation;

    matrixSystem = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixSystem[i] = new float[sizeFirstColumn];
    }

    matrixMain = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixMain[i] = new float[sizeFirstColumn];
    }

    vectorMain = new float[sizeFirstRow];

    matrixSystemPerturbation = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixSystemPerturbation[i] = new float[sizeFirstColumn];
    }

    matrixMainPerturbation = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixMainPerturbation[i] = new float[sizeFirstColumn];
    }

    vectorMainPerturbation = new float[sizeFirstRow];

    srand(time(NULL));

    matrixSystemPerturbation[0][0] = 1;
    matrixSystemPerturbation[1][0] = 4;
    matrixSystemPerturbation[0][1] = 2;
    matrixSystemPerturbation[1][1] = 1;

    matrixSystemPerturbation[0][2] = 7;
    matrixSystemPerturbation[1][2] = 2;

    for (int i = 0; i < sizeFirstRow; i++) {
        for (int j = 0; j < sizeFirstColumn; j++) {
            float r = ((float) rand()) / (float) RAND_MAX;
            matrixSystem[i][j] = r * MAX_MATRIX_VALUE;
            matrixSystemPerturbation[i][j] += matrixSystem[i][j];
            if (j != sizeFirstColumn -1) {
                matrixMain[i][j] = matrixSystem[i][j];
                matrixMainPerturbation[i][j] = matrixSystemPerturbation[i][j];
            } else {
                vectorMain[i] = matrixSystem[i][j];
                vectorMainPerturbation[i] = matrixSystemPerturbation[i][j];
            }
        }
    }


    Matrix systemMatrix = Matrix(matrixSystem, sizeFirstRow, sizeFirstColumn);
    Matrix mainMatrix = Matrix(matrixMain, sizeFirstRow, sizeFirstColumn-1);
    Vector mainVector = Vector(vectorMain, sizeFirstRow);

    Vector answerVector(sizeFirstColumn-1);

    systemMatrix.printSelf();


    int result = solver.GaussMethod(systemMatrix, answerVector);
    if (result != 0) {
        return -1;
    }
    cout << "The simple gauss solution is: " << endl;
    answerVector.printSelf();

    Matrix systemMatrixPertrubation = Matrix(matrixSystemPerturbation, sizeFirstRow, sizeFirstColumn);
    Matrix mainMatrixPertrubation = Matrix(matrixMainPerturbation, sizeFirstRow, sizeFirstColumn-1);
    Vector mainVectorPertrubation = Vector(vectorMainPerturbation, sizeFirstRow);

    Vector answerVectorPertrubation(sizeFirstColumn-1);

    systemMatrixPertrubation.printSelf();


    result = solver.GaussMethod(systemMatrixPertrubation, answerVectorPertrubation);
    if (result != 0) {
        return -1;
    }
    cout << "The simple gauss solution for pertrubation is: " << endl;
    answerVectorPertrubation.printSelf();

    Vector deltaX(answerVectorPertrubation);
    deltaX.substract(answerVector);

    cout << "The deltaX is: " << endl;
    deltaX.printSelf();

    float relativeError = deltaX.calculateEuclideanNorm() / answerVector.calculateEuclideanNorm();

    float condNumber = mainMatrix.getConditionNumber2by2();

    float relation = mainVectorPertrubation.calculateEuclideanNorm() / mainVector.calculateEuclideanNorm() +
            mainMatrixPertrubation.calculateEuclideanNorm() / mainMatrix.calculateEuclideanNorm();

    float upperPoint = relation * condNumber;

    cout << "relative error is: " << relativeError << endl;
    cout << "cond number is: " << condNumber << endl;
    cout << "relation number is: " << relation << endl;
    cout << "upper point is: " << upperPoint << endl;


    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixSystem[i];
    }

    delete [] matrixSystem;

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixMain[i];
    }

    delete [] matrixMain;

    delete [] vectorMain;

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixSystemPerturbation[i];
    }

    delete [] matrixSystemPerturbation;

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixMainPerturbation[i];
    }

    delete [] matrixMainPerturbation;

    delete [] vectorMainPerturbation;

    return 0;
}

int perturbationTestEven() {
    JakobiMethod jakobiMethod = JakobiMethod();
    const int SIZE = 2;
    int sizeFirstRow = SIZE;

    float ** matrixMain;
    float * vectorMain;

    float ** matrixMainPerturbation;
    float * vectorMainPerturbation;

    matrixMain = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixMain[i] = new float[sizeFirstRow];
    }

    vectorMain = new float[sizeFirstRow];

    matrixMainPerturbation = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixMainPerturbation[i] = new float[sizeFirstRow];
    }

    vectorMainPerturbation = new float[sizeFirstRow];

    srand(time(NULL));

    matrixMainPerturbation[0][0] = 1;
    matrixMainPerturbation[1][0] = 4;
    matrixMainPerturbation[0][1] = 2;
    matrixMainPerturbation[1][1] = 1;

    vectorMainPerturbation[0] = 7;
    vectorMainPerturbation[1] = 2;

    for (int i = 0; i < sizeFirstRow; i++) {
        for (int j = 0; j < sizeFirstRow + 1; j++) {
            float r = ((float) rand()) / (float) RAND_MAX;
            float randomValue = r * MAX_MATRIX_VALUE;
            if (i==j) {
                randomValue*=100;
            }
            if (j != sizeFirstRow) {
                matrixMain[i][j] = randomValue;
                matrixMainPerturbation[i][j] += randomValue;
            } else {
                vectorMain[i] = randomValue;
                vectorMainPerturbation[i] += randomValue;
            }
        }
    }


    Matrix mainMatrix = Matrix(matrixMain, sizeFirstRow, sizeFirstRow);
    Vector mainVector = Vector(vectorMain, sizeFirstRow);

    Vector answerVector(sizeFirstRow);

    mainMatrix.printSelf();
    cout << endl;
    mainVector.printSelf();


    jakobiMethod.setPrecision(0.000001);

    bool converges = jakobiMethod.Converges(mainMatrix);
    if (converges) {
        int result = jakobiMethod.Solve(mainMatrix, mainVector, answerVector);
        if (result != 0) {
            return -1;
        }
    } else {
        return 0;
    }
    cout << "The simple jakobi solution is: " << endl;
    answerVector.printSelf();

    Matrix mainMatrixPertrubation = Matrix(matrixMainPerturbation, sizeFirstRow, sizeFirstRow);
    Vector mainVectorPertrubation = Vector(vectorMainPerturbation, sizeFirstRow);

    Vector answerVectorPertrubation(sizeFirstRow);

    mainMatrixPertrubation.printSelf();
    cout << endl;
    mainVectorPertrubation.printSelf();

    converges = jakobiMethod.Converges(mainMatrixPertrubation);
    if (converges) {
        int result = jakobiMethod.Solve(mainMatrixPertrubation, mainVectorPertrubation, answerVectorPertrubation);
        if (result != 0) {
            return -1;
        }
    } else {
        return 0;
    }

    cout << "The simple jakobi solution for pertrubation is: " << endl;
    answerVectorPertrubation.printSelf();

    Vector deltaX(answerVectorPertrubation);
    deltaX.substract(answerVector);

    cout << "The deltaX is: " << endl;
    deltaX.printSelf();

    float relativeError = deltaX.calculateEvenNorm() / answerVector.calculateEvenNorm();

    float condNumber = mainMatrix.getConditionNumber2by2();

    float relation = mainVectorPertrubation.calculateEvenNorm() / mainVector.calculateEvenNorm() +
                     mainMatrixPertrubation.calculateEvenNorm() / mainMatrix.calculateEvenNorm();

    float upperPoint = relation * condNumber;

    cout << "relative error is: " << relativeError << endl;
    cout << "cond number is: " << condNumber << endl;
    cout << "relation number is: " << relation << endl;
    cout << "upper point is: " << upperPoint << endl;


    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixMain[i];
    }

    delete [] matrixMain;

    delete [] vectorMain;

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixMainPerturbation[i];
    }

    delete [] matrixMainPerturbation;

    delete [] vectorMainPerturbation;

    return 0;
}


int jakobiTest() {
    JakobiMethod jakobiMethod = JakobiMethod();
    const int SIZE = 10;
    int sizeFirstRow = SIZE;

    float ** matrixMain;
    float * vectorMain;

    Eigen::MatrixXf EigenA(SIZE, SIZE);
    Eigen::VectorXf Eigenb(SIZE);

    matrixMain = new float*[sizeFirstRow];
    for (int i = 0; i < sizeFirstRow; i++) {
        matrixMain[i] = new float[sizeFirstRow];
    }

    vectorMain = new float[sizeFirstRow];

    srand(time(NULL));


    for (int i = 0; i < sizeFirstRow; i++) {
        for (int j = 0; j < sizeFirstRow + 1; j++) {
            float r = ((float) rand()) / (float) RAND_MAX;
            float randomValue = r * MAX_MATRIX_VALUE;
            if (i==j) {
                randomValue *= 100;
            }
            if (j != sizeFirstRow) {
                matrixMain[i][j] = randomValue;
                EigenA(i, j) = randomValue;
            } else {
                vectorMain[i] = randomValue;
                Eigenb(i) = randomValue;
            }
        }
    }


    Matrix mainMatrix = Matrix(matrixMain, sizeFirstRow, sizeFirstRow);
    Vector mainVector = Vector(vectorMain, sizeFirstRow);

    Vector answerVector(sizeFirstRow);
    Vector answerVectorCopy(sizeFirstRow);

    mainMatrix.printSelf();
    cout << endl;
    mainVector.printSelf();

    jakobiMethod.setPrecision(0.000001);

    bool converges = jakobiMethod.Converges(mainMatrix);
    if (converges) {
        int result = jakobiMethod.Solve(mainMatrix, mainVector, answerVector);
        if (result != 0) {
            return -1;
        }
    } else {
        return 0;
    }

    cout << "The jakobi solution is: " << endl;
    answerVector.printSelf();

    Eigen::VectorXf x = EigenA.completeOrthogonalDecomposition().solve(Eigenb);
    cout << "The eigen solution is:\n" << x << endl;


    Vector controlVector = Vector(sizeFirstRow);
    mainMatrix.multiplyOnVector(answerVector, controlVector);

    cout << "Checking jakobi solution: " << endl;
    controlVector.printSelf();

    Vector mainVectorCopy = Vector(mainVector);
    mainVector.substract(controlVector);

    cout << "Jakobi solution inaccuracy: " << endl;
    mainVector.printSelf();

    cout << "Jakobi solution inaccuracy norm: " << endl;
    cout << mainVector.calculateEvenNorm() << endl;

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixMain[i];
    }

    delete [] matrixMain;

    delete [] vectorMain;

    return 0;
}

int jakobiAndGaussTest() {
    LASolver solver = LASolver();
    JakobiMethod jakobiMethod = JakobiMethod();

    const int SIZE = 10;
    int sizeFirstRow = SIZE;
    int sizeFirstColumn = SIZE+1;

    float ** matrixSystem;
    float ** matrixMain;
    float * vectorMain;

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

    vectorMain = new float[sizeFirstRow];

    srand(time(NULL));



    for (int i = 0; i < sizeFirstRow; i++) {
        for (int j = 0; j < sizeFirstColumn; j++) {
            float r = ((float) rand()) / (float) RAND_MAX;
            matrixSystem[i][j] = r * MAX_MATRIX_VALUE;
            if (i==j) {
                matrixSystem[i][j] *= 100;
            }
            if (j != sizeFirstColumn -1) {
                matrixMain[i][j] = matrixSystem[i][j];
                EigenA(i, j) = matrixSystem[i][j];
            } else {
                vectorMain[i] = matrixSystem[i][j];
                Eigenb(i) = matrixSystem[i][j];
            }
        }
    }


    Matrix systemMatrix = Matrix(matrixSystem, sizeFirstRow, sizeFirstColumn);
    Matrix mainMatrix = Matrix(matrixMain, sizeFirstRow, sizeFirstColumn-1);
//    Matrix mainMatrixCopy = Matrix(mainMatrix);
    Vector mainVector = Vector(vectorMain, sizeFirstRow);
//    Vector mainVectorCopy = Vector(mainVector);

    Vector answerVectorGauss(sizeFirstColumn-1);
    Vector answerVectorJakobi(sizeFirstColumn-1);

    mainMatrix.printSelf();
    cout << endl;
    mainVector.printSelf();

//    systemMatrix.printSelf();

    if (mainMatrix.isDiagonallyDominant()) {
        cout << "diagonally dominant" << endl;
    } else {
        cout << "not diagonally dominant" << endl;
    }

    int result = solver.GaussMethod(systemMatrix, answerVectorGauss);
    if (result != 0) {
        return -1;
    }
    cout << "The simple gauss solution is: " << endl;
    answerVectorGauss.printSelf();



    jakobiMethod.setPrecision(0.000001);

    bool converges = jakobiMethod.Converges(mainMatrix);
    if (converges) {
        result = jakobiMethod.Solve(mainMatrix, mainVector, answerVectorJakobi);
        if (result != 0) {
            return -1;
        }
    } else {
        return 0;
    }

    cout << "The jakobi solution is: " << endl;
    answerVectorJakobi.printSelf();

    Eigen::VectorXf x = EigenA.completeOrthogonalDecomposition().solve(Eigenb);
    cout << "The eigen solution is:\n" << x << endl;


    Vector controlVectorJakobi = Vector(sizeFirstRow);
    mainMatrix.multiplyOnVector(answerVectorJakobi, controlVectorJakobi);

    cout << "Checking jakobi solution: " << endl;
    controlVectorJakobi.printSelf();

    Vector mainVectorCopy = Vector(mainVector);
    mainVectorCopy.substract(controlVectorJakobi);

    cout << "Jakobi solution inaccuracy: " << endl;
    mainVectorCopy.printSelf();

    cout << "Jakobi solution inaccuracy norm: " << endl;
    cout << mainVectorCopy.calculateEvenNorm() << endl;


    Vector controlVectorGauss = Vector(sizeFirstRow);
    mainMatrix.multiplyOnVector(answerVectorGauss, controlVectorGauss);

    cout << "Checking the simple gauss solution: " << endl;
    controlVectorGauss.printSelf();

    Vector mainVectorCopyGauss = Vector(mainVector);
    mainVectorCopyGauss.substract(controlVectorGauss);

    cout << "Gauss solution inaccuracy: " << endl;
    mainVectorCopyGauss.printSelf();


    cout << "Gauss solution inaccuracy norm: " << endl;
    cout << mainVectorCopyGauss.calculateNorm(2) << endl;


    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixSystem[i];
    }

    delete [] matrixSystem;

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixMain[i];
    }

    delete [] matrixMain;

    delete [] vectorMain;

    return 0;
}

int zeidelAndJakobiTest() {
    LASolver solver = LASolver();
    JakobiMethod jakobiMethod = JakobiMethod();
    ZeidelMethod zeidelMethod = ZeidelMethod();

    const int SIZE = 10;
    int sizeFirstRow = SIZE;
    int sizeFirstColumn = SIZE+1;

    float ** matrixSystem;
    float ** matrixMain;
    float * vectorMain;

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

    vectorMain = new float[sizeFirstRow];

    srand(time(NULL));



    for (int i = 0; i < sizeFirstRow; i++) {
        for (int j = 0; j < sizeFirstColumn; j++) {
            float r = ((float) rand()) / (float) RAND_MAX;
            matrixSystem[i][j] = r * MAX_MATRIX_VALUE;
            if (i==j) {
                matrixSystem[i][j] *= 100;
            }
            if (j != sizeFirstColumn -1) {
                matrixMain[i][j] = matrixSystem[i][j];
                EigenA(i, j) = matrixSystem[i][j];
            } else {
                vectorMain[i] = matrixSystem[i][j];
                Eigenb(i) = matrixSystem[i][j];
            }
        }
    }


    Matrix systemMatrix = Matrix(matrixSystem, sizeFirstRow, sizeFirstColumn);
    Matrix mainMatrix = Matrix(matrixMain, sizeFirstRow, sizeFirstColumn-1);
    Vector mainVector = Vector(vectorMain, sizeFirstRow);

    Vector answerVectorGauss(sizeFirstColumn-1);
    Vector answerVectorJakobi(sizeFirstColumn-1);
    Vector answerVectorZeidel(sizeFirstColumn-1);

    mainMatrix.printSelf();
    cout << endl;
    mainVector.printSelf();


    if (mainMatrix.isDiagonallyDominant()) {
        cout << "diagonally dominant" << endl;
    } else {
        cout << "not diagonally dominant" << endl;
    }

    int result = solver.GaussMethod(systemMatrix, answerVectorGauss);
    if (result != 0) {
        return -1;
    }
    cout << "The simple gauss solution is: " << endl;
    answerVectorGauss.printSelf();



    jakobiMethod.setPrecision(0.000001);

    bool converges = jakobiMethod.Converges(mainMatrix);
    if (converges) {
        result = jakobiMethod.Solve(mainMatrix, mainVector, answerVectorJakobi);
        if (result != 0) {
            return -1;
        }
    } else {
        return 0;
    }

    cout << "The jakobi solution is: " << endl;
    answerVectorJakobi.printSelf();

    cout << "The jakobi iterations number is: " << jakobiMethod.getIterationsNumber() << endl;

    zeidelMethod.setPrecision(0.000001);

    bool convergesZeidel = zeidelMethod.Converges(mainMatrix);
    if (convergesZeidel) {
        result = zeidelMethod.Solve(mainMatrix, mainVector, answerVectorZeidel);
        if (result != 0) {
            return -1;
        }
    } else {
        return 0;
    }

    cout << "The zeidel solution is: " << endl;
    answerVectorZeidel.printSelf();

    cout << "The zeidel iterations number is: " << zeidelMethod.getIterationsNumber() << endl;


    Eigen::VectorXf x = EigenA.completeOrthogonalDecomposition().solve(Eigenb);
    cout << "The eigen solution is:\n" << x << endl;


    Vector controlVectorJakobi = Vector(sizeFirstRow);
    mainMatrix.multiplyOnVector(answerVectorJakobi, controlVectorJakobi);

    cout << "Checking jakobi solution: " << endl;
    controlVectorJakobi.printSelf();

    Vector mainVectorCopy = Vector(mainVector);
    mainVectorCopy.substract(controlVectorJakobi);

    cout << "Jakobi solution inaccuracy: " << endl;
    mainVectorCopy.printSelf();

    cout << "Jakobi solution inaccuracy norm: " << endl;
    cout << mainVectorCopy.calculateEvenNorm() << endl;

    Vector controlVectorZeidel = Vector(sizeFirstRow);
    mainMatrix.multiplyOnVector(answerVectorZeidel, controlVectorZeidel);

    cout << "Checking zeidel solution: " << endl;
    controlVectorZeidel.printSelf();

    Vector mainVectorCopyZeidel = Vector(mainVector);
    mainVectorCopyZeidel.substract(controlVectorJakobi);

    cout << "Zeidel solution inaccuracy: " << endl;
    mainVectorCopyZeidel.printSelf();

    cout << "Zeidel solution inaccuracy norm: " << endl;
    cout << mainVectorCopyZeidel.calculateEvenNorm() << endl;


    Vector controlVectorGauss = Vector(sizeFirstRow);
    mainMatrix.multiplyOnVector(answerVectorGauss, controlVectorGauss);

    cout << "Checking the simple gauss solution: " << endl;
    controlVectorGauss.printSelf();

    Vector mainVectorCopyGauss = Vector(mainVector);
    mainVectorCopyGauss.substract(controlVectorGauss);

    cout << "Gauss solution inaccuracy: " << endl;
    mainVectorCopyGauss.printSelf();


    cout << "Gauss solution inaccuracy norm: " << endl;
    cout << mainVectorCopyGauss.calculateNorm(2) << endl;


    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixSystem[i];
    }

    delete [] matrixSystem;

    for (int i = 0; i < sizeFirstRow; i++) {
        delete [] matrixMain[i];
    }

    delete [] matrixMain;

    delete [] vectorMain;

    return 0;
}


int main() {
    cout.precision(8);
    int result = zeidelAndJakobiTest();
    if (result != 0) {
        cout << "Unexpected error during test" << endl;
        return -1;
    }
}