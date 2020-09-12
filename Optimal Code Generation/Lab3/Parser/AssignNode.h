//
// Created by alexis on 07.06.2020.
//

#ifndef LAB3_GOC_ASSIGNNODE_H
#define LAB3_GOC_ASSIGNNODE_H

#include <string>
#include <memory>
#include "Node.h"

using namespace std;

class AssignNode : public Node {
private:
    string name;
    unique_ptr<Node> value;
    LLVMContext *ct;
    IRBuilder<> *b;
    map<string, AllocaInst *> * variables;
public:
    AssignNode() = default;
    AssignNode(const string &name, unique_ptr<Node> value, LLVMContext *ct, map<string, AllocaInst *> * variables, IRBuilder<> *b);
    Value *calculate() override;
};


#endif //LAB3_GOC_ASSIGNNODE_H
