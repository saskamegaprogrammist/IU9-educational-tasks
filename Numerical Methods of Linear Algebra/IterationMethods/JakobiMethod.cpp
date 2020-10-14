//
// Created by alexis on 15.10.2020.
//

#include "JakobiMethod.h"

JakobiMethod::JakobiMethod() {
}

JakobiMethod::JakobiMethod(const float &precision) {
    this->precision = precision;
}

void JakobiMethod::setPrecision(const float &precision) {
    this->precision = precision;
}

bool JakobiMethod::checkConvergence(Matrix main) {
    if (!main.isDiagonallyDominant()) {
        cout << "Method doesn't converge" << endl;
        this->converges = false;
    } else {
        cout << "Method converges" << endl;
        this->converges = true;
    }
    return this->converges;
}

bool JakobiMethod::Converges(const Matrix& main) {
    return this->checkConvergence(main);
}

int JakobiMethod::Solve(const Matrix& mainMatrix, const Vector& mainVector, Vector &answer) {
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
        for (int i = 0; i < dimension; i++) {
            float numerator = mainVector.at(i);
            for (int j = 0; j < dimension; j++) {
                if (i != j) {
                    numerator -= mainMatrix.at(i, j) * initial.at(j);
                }
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

bool JakobiMethod::checkStopCondition(Vector iteration, Vector nextIteration) {
    Vector difference = Vector(nextIteration);
    difference.substract(iteration);
    return difference.calculateEvenNorm() < this->precision;
}

int JakobiMethod::setInitial(Matrix mainMatrix, Vector mainVector, Vector &initial) {
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


