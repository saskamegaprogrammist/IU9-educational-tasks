//
// Created by alexis on 07.09.2020.
//

#ifndef GAUSSMETHOD_VECTOR_H
#define GAUSSMETHOD_VECTOR_H
#include <iostream>
#include <cmath>
using namespace std;

class Vector {
private:
    float * vectorArray;
    int vectorSize;
public:
    Vector();
    Vector(const int &size);
    Vector(const float * array, const int &size);
    Vector(const Vector &original);
    ~Vector();
    bool isEmpty();
    int getVectorSize() const ;
    float at(int i) const;
    void set(int i, float value) const ;
    void add(const Vector &vectorOther);
    void substract(const Vector &vectorOther);
    void multiplyOnVector(const Vector &vectorOther);
    void multiplyOnVector(const Vector &vectorOther, int fromIndex);
    float multiplyScalar(const Vector &vectorOther);
    float getElementsSum(int fromIndex);
    float calculateNorm(int p);
    float calculateEvenNorm();
    float calculateEuclideanNorm();
    void printSelf();

};


#endif //GAUSSMETHOD_VECTOR_H
