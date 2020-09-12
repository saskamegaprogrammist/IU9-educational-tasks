//
// Created by alexis on 08.06.2020.
//

#include <iostream>
#include "IfNode.h"

IfNode::IfNode(unique_ptr<Node> condition, unique_ptr<Node> thenBr, unique_ptr<Node> elseBr, IRBuilder<> *b, LLVMContext *ct, map<string, AllocaInst *> * variables):
        condition(move(condition)), thenBr(move(thenBr)),  elseBr(move(elseBr)), b(b), ct(ct), variables(variables) {}


Value * IfNode::calculate() {
    Value *conditionalValue = condition->calculate();
    if (!conditionalValue)
        return nullptr;

    Function *TheFunction = b->GetInsertBlock()->getParent();


    BasicBlock *ThenBB = BasicBlock::Create(*ct, "then", TheFunction);
    BasicBlock *ElseBB = BasicBlock::Create(*ct, "else");
    BasicBlock *MergeBB = BasicBlock::Create(*ct, "ifcont");

    b->CreateCondBr(conditionalValue, ThenBB, ElseBB);

    b->SetInsertPoint(ThenBB);

    Value *thenValue = thenBr->calculate();
    if (!thenValue)
        return nullptr;

    b->CreateBr(MergeBB);
    ThenBB = b->GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(ElseBB);
    b->SetInsertPoint(ElseBB);

    Value *elseValue = elseBr->calculate();
    if (!elseValue)
        return nullptr;

    b->CreateBr(MergeBB);
    ElseBB = b->GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(MergeBB);
    b->SetInsertPoint(MergeBB);
    PHINode *PN = b->CreatePHI(Type::getInt64Ty(*ct), 2, "iftmp");

    PN->addIncoming(thenValue, ThenBB);
    PN->addIncoming(elseValue, ElseBB);

    return PN;
}
