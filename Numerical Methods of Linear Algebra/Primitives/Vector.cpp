//
// Created by alexis on 07.09.2020.
//

#include "Vector.h"
using namespace std;

Vector::Vector() {
    vectorSize = 0;
    vectorArray = nullptr;
}

Vector::Vector(const float *array, const int &size): vectorSize(size) {
    if (array == nullptr) {
        this->vectorSize = 0;
        this->vectorArray = nullptr;
        return;
    }
    vectorArray = new float [vectorSize];
    for (int i=0; i < vectorSize; i++) {
        vectorArray[i] = array[i];
    }
}

Vector::Vector(const Vector &original) {
    if (original.vectorArray == nullptr) {
        this->vectorSize = 0;
        this->vectorArray = nullptr;
        return;
    }
    this->vectorSize = original.vectorSize;
    this->vectorArray = new float [vectorSize];
    for (int i=0; i < vectorSize; i++) {
        vectorArray[i] = original.vectorArray[i];
    }
}

Vector::Vector(const int &size): vectorSize(size) {
    vectorArray = new float [vectorSize];
    for (int i=0; i < vectorSize; i++) {
        vectorArray[i] = 0;
    }
}

Vector::~Vector() {
    this->vectorSize = 0;
    delete [] this->vectorArray;
}

bool Vector::isEmpty() {
    if (this->vectorSize == 0 && this->vectorArray == nullptr) {
        return true;
    }
}

int Vector::getVectorSize() const {
    return this->vectorSize;
}

void Vector::substract(const Vector &vectorOther) {
    if (this->vectorSize != vectorOther.vectorSize) {
        cout << "Vectors sizes don't match" << endl;
        return;
    }
    for (int i=0; i < vectorSize; i++) {
        vectorArray[i] = vectorArray[i] - vectorOther.vectorArray[i];
    }
}

void Vector::add(const Vector &vectorOther) {
    if (this->vectorSize != vectorOther.vectorSize) {
        cout << "Vectors sizes don't match" << endl;
        return;
    }
    for (int i=0; i < vectorSize; i++) {
        vectorArray[i] = vectorArray[i] + vectorOther.vectorArray[i];
    }
}

float Vector::multiplyScalar(const Vector &vectorOther) {
    if (this->vectorSize != vectorOther.vectorSize) {
        cout << "Vectors sizes don't match" << endl;
        return 0;
    }
    float scalar = 0;
    for (int i = 0; i < vectorSize; i++) {
        scalar += vectorArray[i] * vectorOther.vectorArray[i];
    }
    return scalar;
}

void Vector::multiplyOnVector(const Vector &vectorOther) {
    if (this->vectorSize != vectorOther.vectorSize) {
        cout << "Vectors sizes don't match" << endl;
        return;
    }
    for (int i = 0; i < vectorSize; i++) {
        vectorArray[i] = vectorArray[i] * vectorOther.vectorArray[i];
    }
}

void Vector::multiplyOnVector(const Vector &vectorOther, int fromIndex) {
    if (this->vectorSize != vectorOther.vectorSize) {
        cout << "Vectors sizes don't match" << endl;
        return;
    }
    for (int i = fromIndex; i < vectorSize; i++) {
        vectorArray[i] = vectorArray[i] * vectorOther.vectorArray[i];
    }
}

void Vector::printSelf() {
    for (int i=0; i< this->vectorSize; i++) {
        cout << this->vectorArray[i] << " " ;
    }
    cout << endl;

}


float Vector::at(int i) const {
    if (!(i>= 0 && i < this->vectorSize)) {
        cout << "Index out of range" << endl;
        return -1;
    }
    return this->vectorArray[i];
}

void Vector::set(int i, float value) const {
    this->vectorArray[i] = value;
}

float Vector::getElementsSum(int fromIndex) {
    float sum = 0;
    for (int i = fromIndex; i < this->vectorSize; i++) {
        sum += this->vectorArray[i];
    }
    return sum;
}

float Vector::calculateNorm(int p) {
    float sum = 0;
    float floatP = float(p);
    for (int i = 0; i < this->vectorSize; i++) {
        sum += pow(abs(this->vectorArray[i]), floatP);
    }
    float inv = float(1)/floatP;
    return pow(sum, inv);
}

float Vector::calculateEuclideanNorm() {
    return this->calculateNorm(2);
}

float Vector::calculateEvenNorm() {
    if (this->vectorSize <= 0) {
        cout << "Vector sizes is zero" << endl;
        return 0;
    }
    float max = (abs(this->vectorArray[0]));
    for (int i = 1; i < this->vectorSize; i++) {
        if (abs(this->vectorArray[i]) > max) {
            max = abs(this->vectorArray[i]);
        }
    }
    return max;
}




