//
// Created by alexis on 28.02.20.
//

//
// Created by alexis on 21.02.20.
//

#include <iostream>
#include <limits>
#include <cmath>
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

void calculateLs(float* ys, float* ls, float h, int size) {
    for (int i=1; i < size; i++) {
        ls[i] = 3*(ys[i+1] - 2*ys[i] - ys[i-1]) / (pow(h, 2));
    }
}


int main() {
    cout << "Enter number of koefficients" << endl;
    int size;
    int h;
    float * xs;
    float * ys;
    float * hs;
    float * ls;
    cin >> size;
    int sizeKoeff;
    sizeKoeff = size +1;
    xs = new float[sizeKoeff];
    ys = new float[sizeKoeff];
    ls = new float[size];

    cout << "Enter x's" << endl;
    for  (int i = 0; i < sizeKoeff; i++) {
        cin >> xs[i];
    }
    cout << "Enter y's" << endl;
    for  (int i = 0; i < sizeKoeff; i++) {
        cin >> ys[i];
    }

    h=(xs[size]-xs[0])/size;

    calculateLs(ys, ls, h, size);

    float ** matrix;
    matrix = new float*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new float[size];
    }
    for (int i = 0; i < size; i++) {
        matrix[i][i] = new float[size];
    }

    gaussDiagonal(matrix, answer, variables, size);
    std::cout.precision(15);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield);
//    for (int i=0 ; i < size; i++) {
//        cout << variables[i] << endl;

    for (int i=0 ; i < size; i++) {
        cout << error[i] << endl;
    }
    return 0;
}