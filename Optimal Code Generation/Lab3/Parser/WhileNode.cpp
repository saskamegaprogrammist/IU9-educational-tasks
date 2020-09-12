//
// Created by alexis on 08.06.2020.
//

#include "WhileNode.h"

WhileNode::WhileNode(unique_ptr<Node> condition, unique_ptr<Node> body, IRBuilder<> *b, LLVMContext *ct, map<string, AllocaInst *> * variables):
        condition(move(condition)), body(move(body)), b(b), ct(ct), variables(variables) {}


Value * WhileNode::calculate() {
    Function *TheFunction = b->GetInsertBlock()->getParent();
    BasicBlock *LoopBB = BasicBlock::Create(*ct, "loop", TheFunction);
    b->CreateBr(LoopBB);
    b->SetInsertPoint(LoopBB);

    if (!body->calculate())
        return nullptr;

        Value *conditionalValue = condition->calculate();
        if (!conditionalValue)
            return nullptr;

    BasicBlock *AfterBB =
            BasicBlock::Create(*ct, "afterloop", TheFunction);

    b->CreateCondBr(conditionalValue, LoopBB, AfterBB);
    b->SetInsertPoint(AfterBB);
    return Constant::getNullValue(Type::getInt64Ty(*ct));
}
