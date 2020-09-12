//
// Created by alexis on 07.06.2020.
//

#include "OperatorNode.h"

OperatorNode::OperatorNode(const string &op, unique_ptr<Node> left, unique_ptr<Node> right, IRBuilder<> *b, LLVMContext *ct) :
    op(op), left(move(left)), right(move(right)), b(b), ct(ct) {};

Value * OperatorNode::calculate() {
    Value *leftVal = left->calculate();
    Value *rightVal = right->calculate();
    
    if (op == "+") {
        return b->CreateAdd(leftVal, rightVal, "addv");
    }
    if (op == "-") {
        return b->CreateSub(leftVal, rightVal, "addv");
    }
    if (op == "*") {
        return b->CreateMul(leftVal, rightVal, "mulv");
    }
    if (op == "/") {
        return b->CreateUDiv(leftVal, rightVal, "divv");
    }
    if (op == "==") {
        return b->CreateICmpEQ(leftVal, rightVal, "cmpv");
    }
    if (op == ">") {
        return b->CreateICmpUGT(leftVal, rightVal, "cmpv");
    }
    if (op == ">=") {
        return b->CreateICmpUGE(leftVal, rightVal, "cmpv");
    }
    if (op == "<") {
        return  b->CreateICmpULT(leftVal, rightVal, "cmpv");
    }
    if (op == "<") {
        return b->CreateICmpULE(leftVal, rightVal, "cmpv");
    }
}