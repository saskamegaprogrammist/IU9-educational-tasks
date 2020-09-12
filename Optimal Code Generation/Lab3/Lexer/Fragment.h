//
// Created by alexis on 06.06.2020.
//

#ifndef LAB3_GOC_FRAGMENT_H
#define LAB3_GOC_FRAGMENT_H


#include "Position.h"

class Fragment {
private:
    Position start;
    Position end;
public:
    Fragment() = default;
    Fragment(const Position &start, const Position &end);
    void print();
};


#endif //LAB3_GOC_FRAGMENT_H
