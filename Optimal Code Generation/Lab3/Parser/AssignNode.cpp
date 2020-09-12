//
// Created by alexis on 07.06.2020.
//

#include "AssignNode.h"

AssignNode:: AssignNode(const string &name, unique_ptr<Node> value, LLVMContext *ct, map<string, AllocaInst *> * variables,IRBuilder<> *b) :
        name(name), value(move(value)), ct(ct), b(b), variables(variables) {};

Value * AssignNode::calculate() {
    Value *val = value->calculate();
    if (auto *ex = variables->find(name)->second) {
        b->CreateStore(val, ex);
        return b->CreateLoad(ex);
    } else {
        AllocaInst *allocation = b->CreateAlloca(Type::getInt64Ty(*ct), 0, name);
        variables->insert(pair<string,AllocaInst *>(name,allocation));
         b->CreateStore(val, allocation);
        return b->CreateLoad(allocation);
    }


}