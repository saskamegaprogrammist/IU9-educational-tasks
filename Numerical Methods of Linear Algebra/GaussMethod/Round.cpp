//
// Created by alexis on 08.09.2020.
//

#include "Round.h"
#include <cmath>

using namespace std;

float Round::round(float number) {
    if (abs(number) < presicion) return 0;
    else return number;
}
