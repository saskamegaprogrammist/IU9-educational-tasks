//
// Created by alexis on 18.11.2020.
//

#include "ZeidelMethod.h"

ZeidelMethod::ZeidelMethod() {
}

ZeidelMethod::ZeidelMethod(const float &precision) {
    this->precision = precision;
}

void ZeidelMethod::setPrecision(const float &precision) {
    this->precision = precision;
}

bool ZeidelMethod::checkConvergence(Matrix main) {
    if (!main.isDiagonallyDominant()) {
        cout << "Method doesn't converge" << endl;
        this->converges = false;
    } else {
        cout << "Method converges" << endl;
        this->converges = true;
    }
    return this->converges;
}

bool ZeidelMethod::Converges(const Matrix& main) {
    return this->checkConvergence(main);
}


int ZeidelMethod::Solve(const Matrix& mainMatrix, const Vector& mainVector, Vector &answer) {
    if (!this->converges) {
        cout << "Method doesn't converge" << endl;
        return -1;
    }
    if (mainMatrix.getMatrixRows() != mainMatrix.getMatrixColumns()) {
        cout << "Matrix rows number doesn't matrix columns number" << endl;
        return -1;
    }
    int dimension = mainMatrix.getMatrixColumns();
    Vector initial = Vector(dimension);
    this->setInitial(mainMatrix, mainVector, initial);
    Vector nextIteration = Vector(dimension);
    for (;;) {
        this->iterations++;
        for (int i = 0; i < dimension; i++) {
            float numerator = mainVector.at(i);
            for (int j = 0; j < i; j++) {
                numerator -= mainMatrix.at(i, j) * nextIteration.at(j);
            }
            for (int j = i+1; j < dimension; j++) {
                numerator -= mainMatrix.at(i, j) * initial.at(j);
            }
            nextIteration.set(i, numerator / mainMatrix.at(i, i));
        }
        if (this->checkStopCondition(initial, nextIteration)) {
            break;
        }
        for (int i = 0; i < dimension; i++) {
            initial.set(i, nextIteration.at(i));
        }
    }
    for (int i = 0; i < dimension; i++) {
        answer.set(i, nextIteration.at(i));
    }
    return 0;
}

bool ZeidelMethod::checkStopCondition(Vector iteration, Vector nextIteration) {
    Vector difference = Vector(nextIteration);
    difference.substract(iteration);
    return difference.calculateEvenNorm() < this->precision;
}

int ZeidelMethod::setInitial(Matrix mainMatrix, Vector mainVector, Vector &initial) {
    if (initial.getVectorSize() != mainMatrix.getMatrixRows()) {
        cout << "Vector size is wrong" << endl;
        return -1;
    }
    for (int i=0; i<mainMatrix.getMatrixRows(); i++) {
        if (mainMatrix.at(i, i) == 0) {
            cout << "Main matrix has zero on diagonal" << endl;
            return -1;
        }
        initial.set(i, mainVector.at(i)/mainMatrix.at(i, i));
    }
    return 0;
}

int ZeidelMethod::getIterationsNumber() {
    if (this->iterations == 0) {
        cout << "Method didn't solve anything yet" << endl;
    }
    return this->iterations;
}