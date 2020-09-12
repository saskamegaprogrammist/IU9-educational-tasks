//
// Created by alexis on 07.06.2020.
//

#ifndef LAB3_GOC_PARSER_H
#define LAB3_GOC_PARSER_H


#include "../Lexer/ErrorMessage.h"
#include "../Lexer/Token.h"
#include "PassParameters.h"
#include "LLVMHeaders.h"
#include <vector>
#include <map>

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> builder(TheContext) ;
static unique_ptr<Module> TheModule;
static map<string, AllocaInst *> variables;
static map<string, string> m;

class Parser {

private:
    vector<Token> tokens;
    vector<ErrorMessage> errors;
    Function* generateMain();
    PassParameters parseE(int index);
    PassParameters parseE1(int index, unique_ptr<Node> leftPart);
    PassParameters parseT(int index);
    PassParameters parseT1(int index, unique_ptr<Node> leftPart);
    PassParameters parseF(int index);
    PassParameters parseG(int index);
    PassParameters parseGEND(int index);
    PassParameters parseGSTART(int index, unique_ptr<Node> previous);
    PassParameters parseASSIGN(int index);
    PassParameters parseIF(int index);
    PassParameters parseWHILE(int index);
    PassParameters parseLOG(int index);
    PassParameters parseACTION(int index);
public:
    unique_ptr<Node> parse();
    Parser() = default;
    Parser(const vector<Token> &tokens);
    void generateCode();
    vector<ErrorMessage> getErrors();
    void printErrors();
};


#endif //LAB3_GOC_PARSER_H
