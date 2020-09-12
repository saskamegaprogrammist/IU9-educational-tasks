//
// Created by alexis on 08.06.2020.
//

#ifndef LAB3_GOC_IFNODE_H
#define LAB3_GOC_IFNODE_H


#include <string>
#include <memory>
#include "Node.h"

using namespace std;

class IfNode : public Node {
private:
    unique_ptr<Node> condition;
    unique_ptr<Node> elseBr;
    unique_ptr<Node> thenBr;

    IRBuilder<> *b;
    LLVMContext *ct;
    map<string, AllocaInst *> * variables;
public:
    IfNode() = default;
    IfNode(unique_ptr<Node> condition, unique_ptr<Node> thenBr, unique_ptr<Node> elseBr, IRBuilder<> *b, LLVMContext *ct, map<string, AllocaInst *> * variables);
    Value *calculate() override;
};

#endif //LAB3_GOC_IFNODE_H
