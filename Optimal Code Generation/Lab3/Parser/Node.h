//
// Created by alexis on 07.06.2020.
//

#ifndef LAB3_GOC_NODE_H
#define LAB3_GOC_NODE_H

#include "LLVMHeaders.h"
using namespace llvm;

class Node {
public:
    virtual ~Node() = default;
    Node() = default;
    virtual Value* calculate() = 0;

};


#endif //LAB3_GOC_NODE_H
