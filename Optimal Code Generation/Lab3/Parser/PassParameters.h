//
// Created by alexis on 07.06.2020.
//

#ifndef LAB3_GOC_PASSPARAMETERS_H
#define LAB3_GOC_PASSPARAMETERS_H

#include "Node.h"

#include <memory>
using namespace std;

class PassParameters {
public:
    int index;
    unique_ptr<Node> node;
    PassParameters(int index, unique_ptr<Node> node);

};


#endif //LAB3_GOC_PASSPARAMETERS_H
