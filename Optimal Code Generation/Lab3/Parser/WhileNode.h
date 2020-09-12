//
// Created by alexis on 08.06.2020.
//

#ifndef LAB3_GOC_WHILENODE_H
#define LAB3_GOC_WHILENODE_H

#include <string>
#include <memory>
#include "Node.h"

using namespace std;
class WhileNode : public Node {
private:
    unique_ptr<Node> condition;
    unique_ptr<Node> body;

    IRBuilder<> *b;
    LLVMContext *ct;
    map<string, AllocaInst *> * variables;
public:
    WhileNode() = default;
    WhileNode(unique_ptr<Node> condition, unique_ptr<Node> body, IRBuilder<> *b, LLVMContext *ct, map<string, AllocaInst *> * variables);
    Value *calculate() override;
};



#endif //LAB3_GOC_WHILENODE_H
