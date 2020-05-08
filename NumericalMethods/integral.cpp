//
// Created by alexis on 17.04.2020.
//
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace std;

const float const_A = 0;
const float const_B = M_PI_2;
const int const_N = 2;
const float const_analit = 0.4;
const float eps = 0.001;


float f(float x) {
    return pow(cos(x), 3) * sin(2*x);
}

float s_trapese(float* xs, int n, float h) {
    float result = f(xs[0]) + f(xs[n]);
    for (int i=1; i<=n-1; i++) {
        result += 2*f(xs[i]);
    }
    return h*result/2;
}

float s_simpson(float* xs, int n, float h) {
    float result = f(xs[0]) + f(xs[n]);
    for (int i=1; i<=n-1; i++) {
        if (i%2 == 1) {
            result += 4 * f(xs[i]);
        } else {
            result += 2 * f(xs[i]);
        }
    }
    return h*result/3;
}

float s(float* xs, int n, float h, string method) {
    if (method == "trapeze") {
        return s_trapese(xs, n, h);
    } else {
        if (method == "simpson") {
            return s_simpson(xs, n, h);
        } else {
            return -1;
        }
    }

}

void iterations(string method) {
    int n = const_N;
    float h = (const_B - const_A) / n;
    int n_2 = (const_B - const_A) / 2*h;
    int iterations_number = 0;
    float integral = 0;
    float s_double = 0;
    float richardson = 0;
    float delta = 0;
    float p = 0;
    if (method == "trapeze") {
        p = 2;
    } else {
        if (method == "simpson") {
            p = 4;
        }
        else return;
    }

    for (;;) {
        iterations_number++;
        float *xs;
        xs = new float[n + 1];
        for (int i = 0; i <= n; i++) {
            xs[i] = const_A + i * h;
        }

        float *xs_double;
        xs_double = new float[n_2 + 1];
        for (int i = 0; i <= n_2; i++) {
            xs_double[i] = const_A + i * h*2;
        }
        integral = s(xs, n, h, method);
        s_double = s(xs_double, n_2, 2*h, method);
        delta = abs( integral - s_double ) / (pow(2, p) -1);
        h = h / 2;
        n_2 = n;
        n = (const_B - const_A) / h;

        if (delta < eps) {
            float *xs_half;
            xs_half = new float[n + 1];
            for (int i = 0; i <= n; i++) {
                xs_half[i] = const_A + i * h;
            }
            richardson = (s(xs_half, n, h, method) - integral) / (pow(2, p) -1);
            break;
        }
    }

    cout << iterations_number << " " <<  richardson + integral << " " << richardson << " " << const_analit - integral - richardson << endl;
}

int main() {
    cout.precision(15);
    cout.setf( std::ios::fixed, std:: ios::floatfield);
    cout << const_analit << endl;
    iterations("trapeze");
    iterations("simpson");
}