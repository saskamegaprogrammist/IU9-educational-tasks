//
// Created by alexis on 06.03.2020.
//

#include <iostream>
#include <cmath>
using namespace std;

float calculateSumOfMuls(float* xs, float* ys, int n) {
    float A = 0;
    for (int i=0; i < n; i++) {
        A += xs[i]*ys[i];
    }
    return A;
}


float calculateSum(float* xssquared, int n) {
    float A = 0;
    for (int i=0; i < n; i++) {
       A += xssquared[i];
    }
    return A;
}

float calculatea(float A, float B, float C, float D, float n) {
    float numerator = C - (D*B)/n;
    float denumerator = A - (pow(B, 2)/n);
    return numerator/denumerator;
}

float calculateb(float a, float B, float D, float n) {
    return  (D - a*B)/n;
}

int main() {
    int n;
    float *xs;
    float *ys;
    float *xssquared;
    xs = new float[n];
    xssquared = new float[n];
    ys = new float[n];

    cout << "Enter n" << endl;
    cin >> n;
    cout << "Enter xs" << endl;
    for  (int i = 0; i < n; i++) {
        cin >> xs[i];
        xssquared[i] = pow(xs[i], 2);
    }
    cout << "Enter ys" << endl;
    for  (int i = 0; i < n; i++) {
        cin >> ys[i];
    }
    float A = calculateSum(xssquared, n);
    float B = calculateSum(xs, n);
    float C = calculateSumOfMuls(xs, ys, n);
    float D = calculateSum(ys, n);

    float a = calculatea(A, B, C, D, (float)n);
    float b = calculateb(a, B, D, (float)n);

    cout << a << " " << b ;
}

// 0 0.1 0.198 0.297 0.401 0.502 0.6 0.699 0.802 0.901 1 1.089
// 0 0.1 0.199 0.303 0.399 0.5 0.603 0.702 0.8 0.899 1.001 1.089