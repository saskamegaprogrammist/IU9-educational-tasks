//
// Created by alexis on 24.04.2020.
//
#include <iostream>
#include <limits>
#include <cmath>
using namespace std;

const float x_0 = 1.13882;
const float y_0 = 0.781331;
const float eps = 0.01;

float f1(float x, float y) {
    return cos(x) + y - 1.2;
}

float f2(float x, float y) {
    return 2*x - sin(y-0.5) - 2;
}

float f1x(float x, float y) {
    return (-1)*sin(x);
}

float f1y(float x, float y) {
    return 1;
}

float f2x(float x, float y) {
    return 2;
}

float f2y(float x, float y) {
    return -cos(y-0.5);
}

void multiplyMatrixonVector(float** matrix, float* vector, float* answer, int size) {
    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            answer[i] += matrix[i][j]*vector[j];
        }
    }
}

float calculate_func(float* x_k, float* func_x_k) {
    func_x_k[0] = (-1)*f1(x_k[0], x_k[1]);
    func_x_k[1] = (-1)*f2(x_k[0], x_k[1]);
    //cout <<  func_x_k[0] << " " << func_x_k[1] << endl;
}

float calculate_yakobi(float* x_k, float** yakobi) {
    yakobi[0][0] = f1x(x_k[0], x_k[1]);
    yakobi[0][1] = f1y(x_k[0], x_k[1]);
    yakobi[1][0] = f2x(x_k[0], x_k[1]);
    yakobi[1][1] = f2y(x_k[0], x_k[1]);
    //cout << yakobi [0][0] << " " << yakobi[0][1] << endl << yakobi [1][0] << " " << yakobi[1][1] << endl;
}

float calculate_determinant(float** yakobi) {
    return yakobi[0][0] * yakobi[1][1] - yakobi[1][0]*yakobi[0][1];

}

void calculate_inverted_matrix(float** yakobi, float** yakobi_inverted) {
    float determinant = calculate_determinant(yakobi);
    if (determinant != 0) {
        yakobi_inverted[0][0] = yakobi[1][1] / determinant;
        yakobi_inverted[0][1] = (-1)*yakobi[0][1] / determinant;
        yakobi_inverted[1][0] = (-1)*yakobi[1][0] / determinant;
        yakobi_inverted[1][1] = yakobi[0][0] /determinant;
    }
    else {
        cout << "can't calculate inverted matrix" << endl;
    }
}

float max(float* vars) {
    if (abs(vars[0])> abs(vars[1])) {
        return abs(vars[0]);
    } else return abs(vars[1]);
}

int main() {
    int size = 2;
    float ** yakobi;
    float ** yakobi_inverted;
    float * func;
    float * x_k;
    float * variables;
    yakobi = new float*[size];
    yakobi_inverted = new float*[size];
    func = new float[size];
    variables = new float[size];
    x_k = new float[size];
    for (int i = 0; i < size; i++) {
        yakobi[i] = new float[size];
        yakobi_inverted[i] = new float[size];
    }
    x_k[0] = x_0;
    x_k[1] = y_0;

    float k = 0;
    float pogr = 0;
    for (;;) {
        k++;
        calculate_func(x_k, func);
        calculate_yakobi(x_k, yakobi);
        calculate_inverted_matrix(yakobi, yakobi_inverted);
        multiplyMatrixonVector(yakobi_inverted, func, variables, size);
        //cout << variables[0] << " " << variables[1] << endl;
        x_k[0] += variables[0];
        x_k[1] += variables[1];
        pogr = max(variables);
        if ((pogr) < eps) {
            break;
        }
    }

    std::cout.precision(15);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield);
    cout << x_0 << " " << y_0 << " " << x_k[0] << " " << x_k[1] << " " << k << " " << pogr << endl;

    return 0;
}