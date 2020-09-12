//
// Created by alexis on 07.06.2020.
//

#ifndef LAB3_GOC_VARIABLENODE_H
#define LAB3_GOC_VARIABLENODE_H


#include "Node.h"
#include <string>
using namespace std;

class VariableNode : public Node {
private:
    string var;
    IRBuilder<> *b;
    LLVMContext *ct;
    map<string, AllocaInst *> * variables;
public:
    VariableNode() = default;
    VariableNode(const string &var, IRBuilder<> *b, LLVMContext *ct, map<string, AllocaInst *> * variables);
    Value *calculate() override;
};

#endif //LAB3_GOC_VARIABLENODE_H
