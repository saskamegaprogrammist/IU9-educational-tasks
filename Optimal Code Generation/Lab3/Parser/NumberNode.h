//
// Created by alexis on 07.06.2020.
//

#ifndef LAB3_GOC_NUMBERNODE_H
#define LAB3_GOC_NUMBERNODE_H


#include "Node.h"

class NumberNode : public Node {
private:
    int value;
    LLVMContext *ct;
public:
    NumberNode() = default;
    NumberNode(int value, LLVMContext *ct);
    Value *calculate() override;
};


#endif //LAB3_GOC_NUMBERNODE_H
