//
// Created by alexis on 18.09.2020.
//

#ifndef GAUSSMETHOD_LASOLVER_H
#define GAUSSMETHOD_LASOLVER_H

#include <iostream>
#include "../Primitives/Matrix.h"

using namespace std;

class LASolver {
private:
    int GaussBackwards(Matrix system, Vector & answer);
public:
    LASolver();
    int GaussMethod(Matrix system, Vector & answer);
    int GaussMainSelectionColumn(Matrix system, Vector & answer);
    int GaussMainSelectionRow(Matrix system, Vector & answer);
    int GaussMainSelectionFull(Matrix system, Vector & answer);
};

#endif //GAUSSMETHOD_LASOLVER_H
