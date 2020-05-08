//
// Created by alexis on 10.04.2020.
//

#include <iostream>
#include <cmath>
using namespace std;

const float p = -3;
const float q = 2;
const int n = 10;

const float cauchy_C1 = 0.2;
const float cauchy_C2 = -0.8;
const float cauchy_A = 0.6;
const float cauchy_B = 0.2;

float f(float x) {
    return 2*sin(x);
}

float cauchy(float x) {
    return cauchy_C1*exp(2*x) + cauchy_C2*exp(x) + cauchy_A*cos(x) + cauchy_B*sin(x);
}



void gaussDiagonal(double ** matrix, double * answer, float * variables, int size) {
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
float calculatef(float* xs, double * fv, double h, float n) {
    double h_2 = pow(h,2);
    for (int i=0; i<=n; i++) {
       fv[i] = h_2*f(xs[i]);
    }

}

float calculateInaccuracy(float* y,  float* x, float* e, float* cauchy_v, float n) {
    float max = 0;
    for (int i=0; i<=n; i++) {
        cauchy_v[i] = cauchy(x[i]);
        e[i] = abs(y[i] - cauchy_v[i]);
        if (e[i] > max) {
            max = e[i];
        };
    }
    return max;
}

int main() {
    const clock_t begin_time = clock();

    float a = cauchy(0);
    float b = cauchy(1);
    float h = (float)1/n;

    float* xs;
    xs = new float[n+1];
    for (int i=0; i<=n; i++) {
        xs[i] = i*h;
    }

    double ** matrix;
    matrix = new double *[n-1];
    for (int i = 0; i < n-1; i++) {
        matrix[i] = new double [n-1];
    }

    double h_2 = pow(h,2);
    for (int i = 0; i < n-1; i++) {
        matrix[i][i] = h_2*q - 2;
        if (i != 0) matrix[i][i-1] = (1-p*h/2);
        if (i != n-2) matrix[i][i+1] = (1 + p*h/2);
    }



    double * f;
    f = new double [n+1];
    calculatef(xs, f, h, n);


    float* y;
    y = new float[n+1];
    y[0] = a;
    y[n] = b;

    f[0] -= a*matrix[1][0];
    f[n-2] -= b*matrix[0][1];


    gaussDiagonal(matrix, f, y+1, n-1);

    cout.precision(15);
    cout.setf( std::ios::fixed, std:: ios::floatfield);

    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl ;


    float* e;
    e =  new float[n+1];

    float* cauchy_v;
    cauchy_v =  new float[n+1];

    float error;
    error = calculateInaccuracy(y, xs, e, cauchy_v, n);


    for (int i=0; i<=n; i++) {
        cout << xs[i] << " " << y[i] << " " << cauchy_v[i] << " " << e[i] << endl;
    }
    cout << error << endl;

}