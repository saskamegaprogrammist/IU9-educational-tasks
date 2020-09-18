//
// Created by alexis on 18.09.2020.
//

#include "LASolver.h"

LASolver::LASolver() {

}



int LASolver::GaussMethod(Matrix system, Vector & answer) {
    system.makeTriangular();
    system.printSelf();
    if (system.hasZerosOnDiagonal() || system.getMatrixRows() >= system.getMatrixColumns()) {
        system.removeEmptyRows();
    }
    if (system.hasZerosOnDiagonal() || system.getMatrixRows() < system.getMatrixColumns() - 1) {
        cout << "system has no solution" << endl;
        return -1;
    }
    if (system.getMatrixRows() >= system.getMatrixColumns()) {
        cout << "system has more than one solution" << endl;
        return -1;
    }
    this->GaussBackwards(system, answer);
    return 0;
}

int LASolver::GaussMainSelectionColumn(Matrix system, Vector &answer) {
    system.makeTriangularSelectionColumn();
    system.printSelf();
    if (system.hasZerosOnDiagonal() || system.getMatrixRows() >= system.getMatrixColumns()) {
        system.removeEmptyRows();
    }
    if (system.hasZerosOnDiagonal() || system.getMatrixRows() < system.getMatrixColumns() - 1) {
        cout << "system has no solution" << endl;
        return -1;
    }
    if (system.getMatrixRows() >= system.getMatrixColumns()) {
        cout << "system has more than one solution" << endl;
        return -1;
    }
    this->GaussBackwards(system, answer);
    return 0;
}

int LASolver::GaussBackwards(Matrix system, Vector &answer) {
    for (int i = system.getMatrixRows()-1; i >= 0; i--) {
        Vector answerCopy = Vector(answer);
        Vector row = Vector(system.getLine(i), system.getMatrixColumns()-1);
        answerCopy.multiplyOnVector(row, i);
        float elementSum = answerCopy.getElementsSum(i);
        answer.set(i, (system.at(i, system.getMatrixColumns()-1) - elementSum)/system.at(i, i));
    }
    return 0;
}

int LASolver::GaussMainSelectionRow(Matrix system, Vector &answer) {
    system.makeTriangularSelectionRow();
    if (system.hasZerosOnDiagonal() || system.getMatrixRows() >= system.getMatrixColumns()) {
        system.removeEmptyRows();
    }
    if (system.hasZerosOnDiagonal() || system.getMatrixRows() < system.getMatrixColumns() - 1) {
        cout << "system has no solution" << endl;
        return -1;
    }
    if (system.getMatrixRows() >= system.getMatrixColumns()) {
        cout << "system has more than one solution" << endl;
        return -1;
    }
    this->GaussBackwards(system, answer);
    float * answerCopy = new float [answer.getVectorSize()];
    for (int i = 0; i < answer.getVectorSize(); i++) {
        answerCopy[i] = answer.at(i);
    }
    for (int i = 0; i < answer.getVectorSize(); i++) {
        answer.set(system.getIndexPerm(i), answerCopy[i]);
    }
    delete  [] answerCopy;
    return 0;
}
