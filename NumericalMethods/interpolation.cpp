//
// Created by alexis on 28.02.20.
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

void calculateDs(float* ds, float* cs, float h, int size) {
    for (int i=1; i <= size; i++) {
        ds[i-1] = (cs[i] - cs[i-1])/(3*h);
    }
}


void calculateBs(float* bs, float* cs, float* ys,  float h, int size) {
    for (int i=1; i <= size; i++) {
        bs[i-1] = (ys[i] - ys[i-1])/h - h*(cs[i] + 2*cs[i-1])/3;
    }
}

void calculateLs(float* ys, float* ls, float h, int size) {
    for (int i=1; i < size; i++) {
        ls[i-1] = 3*(ys[i+1] - 2*ys[i] - ys[i-1]) / (pow(h, 2));
    }
}

void calculateYs(float* xs, float* ys, int sizeKoeff) {
    for (int i=0; i < sizeKoeff; i++) {
        ys[i] = exp(xs[i]);
    }
}

void calculateXs(float* xs, int n, float h) {
    for (int i=1; i < n; i++) {
        xs[i] = xs[0] + i*h;
    }
}

void calculateSs(float* ss, float* xs, float* ys,  float* bs,  float* cs,  float* ds, float h, int sizeKoeff) {
    ss[0] = ys[0];
    for (int i=1; i < sizeKoeff; i++) {
        ss[i] = ys[i-1] + bs[i-1]*h + cs[i-1]*pow(h, 2) + ds[i-1]*pow(h, 3);
    }
}

int main() {
    float h;
    int n;

    int sizeKoeff;
    float * xs;
    float * ys;
    float * ls;
    float * cs;
    float * ds;
    float * bs;
    float * ss;

    cout << "Enter n" << endl;
    cin >> n;
    n*=2;

    sizeKoeff = n + 1;
    xs = new float[sizeKoeff];
    ys = new float[sizeKoeff];
    ss = new float[sizeKoeff];
    cs = new float[sizeKoeff];
    ls = new float[n];
    bs = new float[n];
    ds = new float[n];
    cout << "Enter a" << endl;
    cin >> xs[0];
    cout << "Enter b" << endl;
    cin >> xs[sizeKoeff-1];

    h=(xs[sizeKoeff-1]-xs[0])/(float)n;

    calculateXs(xs, n, h);
    calculateYs(xs, ys, sizeKoeff);
    calculateLs(ys, ls, h, n);

    float ** matrix;
    matrix = new float*[n-1];
    for (int i = 0; i < n-1; i++) {
        matrix[i] = new float[n-1];
    }
    for (int i = 0; i < n-1; i++) {
        matrix[i][i] = 4;
        if (i != 0) matrix[i][i-1] = 1;
        if (i != n-1) matrix[i][i+1] = 1;
    }

    cs[0] = cs[n] =  0;
    gaussDiagonal(matrix, ls, cs+1, n-1);

    calculateBs(bs, cs, ys, h, n);
    calculateDs(ds, cs, h, n);
    calculateSs(ss, xs, ys, bs, cs, ds, h, sizeKoeff);
    std::cout.precision(15);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield);
    for (int i=0 ; i < sizeKoeff; i++) {
        cout << xs[i] << " " << ys[i] << " " << ss[i] << " " << ss[i] - ys[i] << endl;
    }

    return 0;
}