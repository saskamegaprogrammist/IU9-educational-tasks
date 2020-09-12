//
// Created by alexis on 06.06.2020.
//

#include "llvm/ADT/APInt.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;


Function* generateMain() {
    FunctionType *FT = FunctionType::get(Type::getInt64Ty(TheContext), false);
    Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, "main", TheModule.get());
    BasicBlock *BB = BasicBlock::Create(TheContext, "main", TheFunction);
    Builder.SetInsertPoint(BB);

    float a = 353;
    float b = 48;
    Value *L = ConstantInt::get(TheContext, APInt(64, a, false));
    Value *R = ConstantInt::get(TheContext, APInt(64, b, false));

    Value *RetVal = Builder.CreateFAdd(L, R, "add");
    Builder.CreateRet(RetVal);
    verifyFunction(*TheFunction);
    return TheFunction;
}


int main() {
    TheModule = llvm::make_unique<Module>("Lab 2", TheContext);

    auto *Fn = generateMain();
    Fn->print(errs());

    return 0;
}
