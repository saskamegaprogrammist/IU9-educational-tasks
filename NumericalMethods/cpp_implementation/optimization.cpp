//
// Created by alexis on 08.05.2020.
//

#include <iostream>
#include <cmath>
using namespace std;

const float a = -1;
const float b = 0;
const float eps = 0.1;

float f(float x) {
    return pow(x, 6) + 3*pow(x,2) +6*x - 1;
}

float f_1(float x) {
    return 6*(pow(x, 5) + x + 1);
}

float f_2(float x) {
    return 30*pow(x, 4) + 6;
}

void dihotomia() {
    float delta = eps/3;
    float a_k = a;
    float b_k = b;
    float x;
    float x_1;
    float x_2;
    float k = 0;
    float eps_double = 2*eps;
    while (abs(b_k - a_k) > eps_double) {
        k++;
        x = (a_k + b_k) / 2;
        x_1 = x-delta;
        x_2 = x+delta;
        if (f(x_1) <= f(x_2)) {
            b_k = x_1;
        } else {
            a_k = x_1;
        }
    }
    x = (a_k + b_k) / 2;
    cout << x << " " <<  f(x) << " " << k << endl;

}

void goldenRatio() {
    float ratio_1 = (3 - sqrt(5))/2;
    float ratio_2 = (sqrt(5) - 1)/2;
    float a_k = a;
    float b_k = b;
    float x;
    float x_1;
    float x_2;
    float k = 0;
    float eps_double = 2*eps;
    while (abs(b_k - a_k)  > eps_double) {
        k++;
        x_1 = a_k + ratio_1*(b_k - a_k);
        x_2 = a_k + ratio_2*(b_k - a_k);
        if (f(x_1) <= f(x_2)) {
            b_k = x_2;
        } else {
            a_k = x_1;
        }
    }
    x =  a_k + ratio_2*(b_k - a_k);
    cout << x << " " <<  f(x) << " " << k << endl;
}

void newton() {
    float x  = (a+b)/2;
    float x_k = x;
    float k = 0;
    for(;;) {
        k++;
        float x_swap = x_k;
        x_k = x - f_1(x)/f_2(x);
        x = x_swap;
        if (abs(x_k - x) <= eps) break;
    }
    x =  x - f_1(x)/f_2(x);
    cout << x << " " <<  f(x) << " " << k << endl;
}



int main() {
    std::cout.precision(15);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield);

    dihotomia();
    goldenRatio();
    newton();

    return 0;
}