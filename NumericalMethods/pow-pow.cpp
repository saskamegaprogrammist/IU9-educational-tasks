//
// Created by alexis on 27.03.2020.
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
    return cauchy_C1* + cauchy_C2*exp(x) + cauchy_A*cos(x) + cauchy_B*sin(x);
}

float calculateY0(float* xs, float* y0, float h, float n) {
    for (int i=1; i<n; i++) {
        y0[i+1] = (f(xs[i])*pow(h, 2) + (2-q*pow(h, 2))*y0[i] - (1-p*h/2)*y0[i-1]) / (1+p*h/2);
    }
}

float calculateY1(float* xs, float* y1, float h, float n) {
    for (int i=1; i<n; i++) {
        y1[i+1] = ((2-q*pow(h, 2))*y1[i] - (1-p*h/2)*y1[i-1]) / (1+p*h/2);
    }
}

float calculateY(float* y, float* y0, float* y1, float n, float C1) {
    for (int i=0; i<=n; i++) {
        y[i] = y0[i] + C1*y1[i];
    }
}

int main() {
    float a = cauchy(0);
    float b = cauchy(1);
    float A = cauchy(a);
    float B = cauchy(b);
    float h = (b-a)/n;

    float* xs;
    xs = new float[n+1];
    for (int i=0; i<=n; i++) {
        xs[i] = a + i*h;
    }

    float* y0;
    y0 = new float[n+1];
    y0[0] = A;
    y0[1] = A + h;


    float* y1;
    y1 = new float[n+1];
    y1[0] = 0;
    y1[1] = h;
    calculateY0(xs, y0, h, n);
    calculateY1(xs, y1, h, n);
    float C1 = (B-y0[n])/y1[n];

    float* y;
    y = new float[n+1];
    calculateY(y, y0, y1, n, C1);


    cout.precision(15);
    cout.setf( std::ios::fixed, std:: ios::floatfield);

    for (int i=0; i<=n; i++) {
        cout << xs[i] << " " << y[i] << " " << cauchy(xs[i]) << " " << cauchy(xs[i]) - y[i] << endl;
    }

}