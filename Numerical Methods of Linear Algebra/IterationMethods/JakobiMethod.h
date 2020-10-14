//
// Created by alexis on 15.10.2020.
//

#ifndef TEST_JAKOBIMETHOD_H
#define TEST_JAKOBIMETHOD_H

#include "../Primitives/Matrix.h"

using namespace std;

class JakobiMethod {
private:
    float precision = 0.0001;
    bool converges = false;
    bool checkConvergence(Matrix main);
    bool checkStopCondition(Vector iteration, Vector nextIteration);
    int setInitial(Matrix mainMatrix, Vector mainVector, Vector & initial);
public:
    JakobiMethod();
    JakobiMethod(const float& precision);
    void setPrecision(const float& precision);
    bool Converges(const Matrix& main);
    int Solve(const Matrix& mainMatrix, const Vector& mainVector, Vector & answer);
};


#endif //TEST_JAKOBIMETHOD_H
