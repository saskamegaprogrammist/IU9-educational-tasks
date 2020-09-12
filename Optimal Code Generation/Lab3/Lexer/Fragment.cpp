//
// Created by alexis on 06.06.2020.
//

#include "Fragment.h"
#include <iostream>

Fragment:: Fragment(const Position &start, const Position &end):
        start(start), end(end) {}


void Fragment::print() {
    cout << "(" << start.getLine() << " ," << start.getPosition() << ") - (" << end.getLine() << " ," << end.getPosition() << ")";
}