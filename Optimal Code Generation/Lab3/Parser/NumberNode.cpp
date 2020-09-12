//
// Created by alexis on 07.06.2020.
//

#include "NumberNode.h"

NumberNode::NumberNode(int value, LLVMContext *ct) : value(value), ct(ct) {}

Value * NumberNode::calculate() {
    return  ConstantInt::get(*ct, APInt(64, this->value, false));
}