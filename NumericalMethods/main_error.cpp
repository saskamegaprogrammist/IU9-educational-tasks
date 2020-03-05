//
// Created by alexis on 21.02.20.
//

#include <iostream>
#include <limits>
using namespace std;


void gaussDiagonal(float** matrix, float* answer, float* variables, int size) {
    float * alphas;
    float * betas;
    alphas = new float[size];
    betas = new float[size];
    alphas[0] = -matrix[0][1] / matrix[0][0];
    betas[0] = answer[0] / matrix[0][0];
    for (int i=1; i < size; i++) {
        float koeff = matrix[i][i] + matrix[i][i-1]*alphas[i-1];
        if (i != size-1) alphas[i] = -matrix[i][i+1] / koeff;
        betas[i] = (answer[i] - matrix[i][i-1]* betas[i-1]) / koeff;
    }
    variables[size-1] = betas[size-1];
    for (int i=size-2; i>=0; i--) {
        variables[i] = alphas[i]*variables[i+1] + betas[i];
    }
    return;

}

void multiplyMatrixonVector(float** matrix, float* vector, float* answer, int size) {
    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            answer[i] += matrix[i][j]*vector[j];
        }
    }
}

void substractVectors(float* vector1, float* vector2, float* newVector, int size) {
    for (int i=0; i < size; i++) {
        newVector[i] = vector1[i] - vector2[i];
    }
}

void addVectors(float* vector1, float* vector2, int size) {
    for (int i=0; i < size; i++) {
        vector1[i] += vector2[i];
    }
}

int main() {
    cout << "Enter size of the matrix" << endl;
    int size;
    float ** matrix;
    float ** matrixInverted;
    float * answer;
    float * variables;
    float * nevazka;
    float * error;
    float * dStarred;
    cin >> size;
    matrix = new float*[size];
    matrixInverted = new float*[size];
    answer = new float[size];
    nevazka = new float[size];
    error = new float[size];
    dStarred = new float[size];
    variables = new float[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new float[size];
    }
    for (int i = 0; i < size; i++) {
        matrixInverted[i] = new float[size];
    }
    cout << "Enter matrix" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> matrix[i][j];
        }
    }
    cout << "Enter inverted matrix" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> matrixInverted[i][j];
        }
    }
    cout << "Enter answer" << endl;
    for  (int i = 0; i < size; i++) {
        cin >> answer[i];
    }
    gaussDiagonal(matrix, answer, variables, size);
    std::cout.precision(15);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield);
//    for (int i=0 ; i < size; i++) {
//        cout << variables[i] << endl;
//    }
    multiplyMatrixonVector(matrix, variables, dStarred, size);
    substractVectors(answer, dStarred, nevazka, size);
    multiplyMatrixonVector(matrixInverted, nevazka, error, size);
    addVectors(variables,error, size);

    for (int i=0 ; i < size; i++) {
        cout << error[i] << endl;
    }
    return 0;
}
////
//3 1 0 0
//1 3 1 0
//0 1 3 1
//0 0 1 3
//
//0.38181818181	-0.14545454545	0.05454545454	-0.01818181818
//-0.14545454545	0.43636363636	-0.16363636363	0.05454545454
//0.05454545454	-0.16363636363	0.43636363636	-0.14545454545
//-0.01818181818	0.05454545454	-0.14545454545	0.38181818181
//
//4 5 5 4

//1.000000000000000
//0.999999880790710
//1.000000000000000
//1.000000000000000
// отразить в отчете, что нет методологической погрешности, но нет вычислительной