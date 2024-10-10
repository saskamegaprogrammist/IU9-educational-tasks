//
// Created by alexis on 15.05.2020.
//

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace std;

const float const_A = 1;
const float const_B = 3;
const float const_C = 0;
const float const_D = 1;
const int const_N = 2;
const float const_analit = 1.54518;
const float eps = 0.001;


float f(float x, float y) {
    return logf(y/x);
}

float alpha_1(float x) {
    return x;
}

float alpha_2(float x) {
    return 2*x;
}

float y(float u, float v) {
    return (1-v)* alpha_1(u) + v*(alpha_2(u));
}

float jakobian(float u) {
    return abs(alpha_2(u) -alpha_1(u));
}

float q_const_trapese(int i, int j, int n, int m) {
    if (i==0 || i==n) {
        if (j==0 || j==m) return (1/4);
        else return (1/2);
    } else {
        if (j==0 || j==m) return (1/2);
        else return 1;
    }
}


float s_trapese(float* xs, float* ys, int n, int m, float h_x, float h_y) {
    float result = 0;
    for (int i=0; i<=n; i++) {
        for (int j=0; j<=m; j++) {
            result += q_const_trapese(i, j, n, m)*f(xs[i],y(xs[i],ys[j]))*jakobian(xs[i]);
        };
    }
    return h_x*h_y*result;
}

float s_cell(float* xs, float* ys, int n, int m, float h_x, float h_y) {
    float result = 0;
    float h_x_half = h_x/2;
    float h_y_half = h_y/2;
    for (int i=0; i<=n; i++) {
        for (int j=0; j<=m; j++) {
            result += f(xs[i] + h_x_half,y(xs[i],ys[j]) + h_y_half)*jakobian(xs[i]);
        };
    }
    return h_x*h_y*result;
}

float s(float* xs, float* ys, int n, int m, float h_x, float h_y, string method) {
    if (method == "trapeze") {
        return s_trapese(xs, ys, n, m, h_x, h_y);
    } else {
        if (method == "cell") {
            return s_cell(xs, ys, n, m, h_x, h_y);
        } else {
            return -1;
        }
    }

}

void iterations(string method) {
    float h_x = sqrt(eps);
    float h_y = h_x;
    int n = (const_B - const_A) / h_x;
    int n_2 = (const_B - const_A) / 2*h_x;
    int m = (const_D - const_C) / h_y;
    int m_2 = (const_D - const_C) / 2*h_y;
    int iterations_number = 0;
    float integral = 0;
    float s_double = 0;
    float richardson = 0;
    float delta = 0;
    float p = 2;

    for (;;) {
        iterations_number++;
        float *xs;
        xs = new float[n + 1];
        for (int i = 0; i <= n; i++) {
            xs[i] = const_A + i * h_x;
        }


        float *ys;
        ys = new float[m + 1];
        for (int i = 0; i <= m; i++) {
            ys[i] = const_C + i * h_y;
        }

        float *xs_double;
        xs_double = new float[n_2 + 1];
        for (int i = 0; i <= n_2; i++) {
            xs_double[i] = const_A + i * h_x*2;
        }

        float *ys_double;
        ys_double = new float[m_2 + 1];
        for (int i = 0; i <= m_2; i++) {
            ys_double[i] = const_C + i * h_y*2;
        }

        integral = s(xs, ys, n, m, h_x, h_y, method);
        s_double = s(xs_double, ys_double, n_2, m_2, 2*h_x, 2*h_y, method);
        delta = abs( integral - s_double ) / (pow(2, p) -1);
        h_x = h_x / 2;
        h_y = h_y / 2;
        n_2 = n;
        m_2 = m;
        n = (const_B - const_A) / h_x;
        m = (const_D - const_C) / h_y;

        if (delta < eps) {
            float *xs_half;
            xs_half = new float[n + 1];
            for (int i = 0; i <= n; i++) {
                xs_half[i] = const_A + i * h_x;
            }

            float *ys_half;
            ys_half = new float[m + 1];
            for (int i = 0; i <= m; i++) {
                ys_half[i] = const_C + i * h_y;
            }

            richardson = abs(s(xs_half, ys_half, n, m, h_x, h_y, method) - integral) / (pow(2, p) -1);
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
    iterations("cell");
}