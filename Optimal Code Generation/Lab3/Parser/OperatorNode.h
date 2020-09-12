//
// Created by alexis on 07.06.2020.
//

#ifndef LAB3_GOC_OPERATORNODE_H
#define LAB3_GOC_OPERATORNODE_H


#include <string>
#include <memory>
#include "Node.h"

using namespace std;

class OperatorNode : public Node {
private:
    string op;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
    LLVMContext *ct;
    IRBuilder<> *b;
public:
    OperatorNode() = default;
    OperatorNode(const string &op, unique_ptr<Node> left, unique_ptr<Node> right, IRBuilder<> *b, LLVMContext *ct);
    Value *calculate() override;
};


#endif //LAB3_GOC_OPERATORNODE_H
