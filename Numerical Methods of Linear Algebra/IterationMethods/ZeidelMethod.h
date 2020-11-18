//
// Created by alexis on 18.11.2020.
//

#ifndef TEST_ZEIDELMETHOD_H
#define TEST_ZEIDELMETHOD_H

#include "../Primitives/Matrix.h"

using namespace std;

class ZeidelMethod {
private:
    float precision = 0.0001;
    bool converges = false;
    int iterations = 0;
    bool checkConvergence(Matrix main);
    bool checkStopCondition(Vector iteration, Vector nextIteration);
    int setInitial(Matrix mainMatrix, Vector mainVector, Vector & initial);
public:
    ZeidelMethod();
    ZeidelMethod(const float& precision);
    void setPrecision(const float& precision);
    bool Converges(const Matrix& main);
    int Solve(const Matrix& mainMatrix, const Vector& mainVector, Vector & answer);
    int getIterationsNumber();
};

#endif //TEST_ZEIDELMETHOD_H
