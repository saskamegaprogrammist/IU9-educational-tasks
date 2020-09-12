//
// Created by alexis on 07.06.2020.
//

#include <iostream>
#include "Parser.h"
#include "PassParameters.h"
#include "NumberNode.h"
#include "OperatorNode.h"
#include "AssignNode.h"
#include "VariableNode.h"
#include "IfNode.h"
#include "WhileNode.h"

static const int ERRORIND = -1;



Parser::Parser(const vector<Token> & tokens) : tokens(tokens) {}

PassParameters Parser::parseWHILE(int index) {
    Token tok = tokens.at(index);
    if (tok.getType() == LEFT_BR) {
        index++;
        PassParameters pass = parseLOG(index);
        index = pass.index;
        tok = tokens.at(index);
        if (tok.getType() != RIGHT_BR) {
            this->errors.emplace_back(ErrorMessage(string("Expected RIGHT BRACKET"),
                                                   tok.getCoords()));
            return PassParameters(ERRORIND, nullptr);
        }
        index++;
        PassParameters bodyPass = parseACTION(index);

        index = bodyPass.index;
        return PassParameters(index,
                              llvm::make_unique<WhileNode>(move(pass.node), move(bodyPass.node),
                                                        &builder, &TheContext, &variables));


    }
    this->errors.emplace_back(ErrorMessage(string("Wrong token in IF statement"),
                                           tok.getCoords()));
    return PassParameters(ERRORIND, nullptr);
}

PassParameters Parser::parseIF(int index) {
    Token tok = tokens.at(index);
    if (tok.getType() == LEFT_BR) {
        index++;
        PassParameters pass = parseLOG(index);
        index = pass.index;
        tok = tokens.at(index);
        if (tok.getType() != RIGHT_BR) {
            this->errors.emplace_back(ErrorMessage(string("Expected RIGHT BRACKET"),
                                                   tok.getCoords()));
            return PassParameters(ERRORIND, nullptr);
        }
        index++;
        tok = tokens.at(index);
        if (tok.getType() == KEYWORD) {
            if (tok.getAttr() == "then") {
                index++;
                PassParameters thenPass = parseACTION(index);
                index = thenPass.index;
                tok = tokens.at(index);
                if (tok.getType() == KEYWORD) {
                    if (tok.getAttr() == "else") {
                        index++;
                        PassParameters elsePass = parseACTION(index);
                        index = elsePass.index;
                        return PassParameters(index, llvm::make_unique<IfNode>(move(pass.node), move(thenPass.node), move(elsePass.node), &builder, &TheContext, &variables));
                    }
                }
            }
        }
    }
    this->errors.emplace_back(ErrorMessage(string("Wrong token in IF statement"),
                                             tok.getCoords()));
    return PassParameters(ERRORIND, nullptr);
}

PassParameters Parser::parseLOG(int index) {
    PassParameters pass = parseE(index);
    index = pass.index;
    Token tok = tokens.at(index);
    if (tok.getType() == OPERATOR) {
        string tokAttr = tok.getAttr();
        if (tokAttr == ">" || tokAttr == "<" || tokAttr == "==" || tokAttr == ">=" || tokAttr == "<=" ) {
            index++;
            PassParameters rightPart = parseE(index);
            return PassParameters(rightPart.index, llvm::make_unique<OperatorNode>(tokAttr, move(pass.node), move(rightPart.node), &builder, &TheContext));
        }
        else {
            return PassParameters(pass.index, move(pass.node));
        }
    } else {
        return PassParameters(pass.index, move(pass.node));
    }
}

PassParameters Parser::parseF(int index) {
    Token startTok = tokens.at(index);
    if (startTok.getType() == LEFT_BR) {
       index++;
       PassParameters pass = parseE(index);
       if (tokens.at(pass.index).getType() != RIGHT_BR) {
           this->errors.emplace_back(ErrorMessage(string("Expected RIGHT BRACKET"),
                                                  startTok.getCoords()));
       }
       pass.index++;
       return pass;
    } else if (startTok.getType() == IDENTIFICATOR) {
        index++;
        return PassParameters(index, llvm::make_unique<VariableNode>(startTok.getAttr(), &builder,  &TheContext, &variables));
    } else if (startTok.getType() == VALUE_TYPE) {
        index++;
        return PassParameters(index, llvm::make_unique<NumberNode>(stoi(startTok.getAttr()), &TheContext));
    } else {
        this->errors.emplace_back(ErrorMessage(string("Wrong token"),
                                               startTok.getCoords()));
        return PassParameters(ERRORIND, nullptr);
    }
}

PassParameters Parser::parseT1(int index, unique_ptr<Node> leftPart) {
    Token startTok = tokens.at(index);
    if (startTok.getType() == OPERATOR) {
        string tokAttr = startTok.getAttr();
        if (tokAttr == "*" || tokAttr == "/") {
            index++;
            PassParameters rightPart = parseT(index);
            return PassParameters(rightPart.index, llvm::make_unique<OperatorNode>(tokAttr, move(leftPart), move(rightPart.node), &builder, &TheContext));
        }
    }
    return PassParameters(index, move(leftPart));

}


PassParameters Parser::parseE1(int index, unique_ptr<Node> leftPart) {
    Token startTok = tokens.at(index);
    if (startTok.getType() == OPERATOR) {
        string tokAttr = startTok.getAttr();
        if (tokAttr == "+" || tokAttr == "-") {
            index++;
            PassParameters rightPart = parseE(index);
            return PassParameters(rightPart.index, llvm::make_unique<OperatorNode>(tokAttr, move(leftPart), move(rightPart.node),&builder, &TheContext));
        }
    }
    return PassParameters(index, move(leftPart));
}


PassParameters Parser::parseT(int index) {
    PassParameters pass = parseF(index);
    if (pass.index == ERRORIND) return pass;
    else {
        return parseT1(pass.index, move(pass.node));
    }
}


PassParameters Parser::parseE(int index) {
    PassParameters pass = parseT(index);
    if (pass.index == ERRORIND) return pass;
    else {
        return parseE1(pass.index, move(pass.node));
    }
}

PassParameters Parser::parseASSIGN(int index) {
    Token startTok = tokens.at(index);
    if (startTok.getType() == IDENTIFICATOR) {
        string varName = startTok.getAttr();
        index++;
        if (tokens.at(index).getType() != EQ) {
            this->errors.emplace_back(ErrorMessage(string("Expected ASSIGN"),
                                                   startTok.getCoords()));
            return PassParameters(ERRORIND, nullptr);
        }
        index++;
        PassParameters pass = this->parseE(index);
        return PassParameters(pass.index, llvm::make_unique<AssignNode>(varName, move(pass.node), &TheContext, &variables, &builder));
    }
    this->errors.emplace_back(ErrorMessage(string("Expected IDENTIFICATOR"),
                                           startTok.getCoords()));
    return PassParameters(ERRORIND, nullptr);
}

PassParameters Parser::parseACTION(int index) {
    Token tok = tokens.at(index);
    PassParameters pass = PassParameters(ERRORIND, nullptr);
    if (tok.getType() == KEYWORD) {
        if (tok.getAttr() == "if") {
            index++;
            pass = parseIF(index);
            return PassParameters(pass.index, move(pass.node));
        }
        if (tok.getAttr() == "while") {
            index++;
            pass = parseWHILE(index);
            return PassParameters(pass.index, move(pass.node));
        }
        return pass;
    } else {
        pass = parseASSIGN(index);
        index = pass.index;
        tok = tokens.at(index);
        if (tok.getType() != SEMICOLON) {
            this->errors.emplace_back(ErrorMessage(string("Expected SEMICOLON"),
                                                   tok.getCoords()));
            return PassParameters(ERRORIND, nullptr);
        }
        index++;
    }

    return PassParameters(index, move(pass.node));
}

PassParameters Parser::parseGEND(int index) {
    Token startTok = tokens.at(index);
    if (startTok.getType() == KEYWORD && startTok.getAttr() == "return") {
        index++;
        return parseE(index);
    } else if (startTok.getType() == END) {
        return PassParameters(index, nullptr);
    } else {
        this->errors.emplace_back(ErrorMessage(string("Expected return or EOF"),
                                               startTok.getCoords()));
        return PassParameters(ERRORIND, nullptr);
    }
}

PassParameters Parser::parseGSTART(int index, unique_ptr<Node> previous) {
    if (this->tokens.at(index).getType() == END)
        return PassParameters(index, move(previous));
    PassParameters pass = parseACTION(index);
    if (pass.index == ERRORIND) {
        return PassParameters(index, move(previous));
    }
    pass.node->calculate();
    return parseGSTART(pass.index, move(pass.node));
}

PassParameters Parser::parseG(int index) {
    PassParameters pass = parseGSTART(index, nullptr);
    return parseGEND(pass.index);
}


unique_ptr<Node>  Parser::parse() {
    if (tokens.empty()) return nullptr;
    else {
        PassParameters pass = parseG(0);
        return move(pass.node);
    }
}

Function* Parser::generateMain() {
    FunctionType *FT = FunctionType::get(Type::getInt64Ty(TheContext), false);
    Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, "main", TheModule.get());
    BasicBlock *BB = BasicBlock::Create(TheContext, "main", TheFunction);
    builder.SetInsertPoint(BB);

    unique_ptr<Node> p = parse();
    Value * body;
    if (p != nullptr) {
        body = p->calculate();
    } else {
        body =  ConstantInt::get(TheContext, APInt(64, 0, false));

    }
    builder.CreateRet(body);
    verifyFunction(*TheFunction);
//    TheFunction->viewCFG();
    return TheFunction;
}

void Parser::generateCode() {
    TheModule = llvm::make_unique<Module>("Lab 3", TheContext);

    auto *MainF = generateMain();
    TheModule->print(errs(), nullptr);
}

void Parser::printErrors() {
    if (!this->errors.empty()) {
        for (int i=0; i<errors.size(); i++) {
            errors.at(i).print();
        }
    }

}