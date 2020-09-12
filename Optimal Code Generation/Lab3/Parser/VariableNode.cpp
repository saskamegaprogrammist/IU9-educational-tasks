//
// Created by alexis on 07.06.2020.
//

#include <iostream>
#include "VariableNode.h"

VariableNode::VariableNode(const string &var, IRBuilder<> *b, LLVMContext *ct, map<string, AllocaInst *> * variables) :
        var(var), b(b), ct(ct), variables(variables) {}

Value *VariableNode::calculate() {
    Value *value = variables->find(var)->second;
    if (!value) return nullptr;
    return b->CreateLoad(value, var.c_str());
};
