//
// Created by alexis on 06.06.2020.
//

#ifndef LAB3_GOC_LEXER_H
#define LAB3_GOC_LEXER_H


#include "Token.h"
#include "ErrorMessage.h"
#include <vector>
class Lexer {
private:
    vector<Token> tokens;
    vector<ErrorMessage> errors;
    string file;
    Position position;
    void lex();
public:
    Lexer() = default;
    Lexer(const string &file);
    vector<Token> getTokenSet();
    vector<ErrorMessage> getErrors();
    void printTokens();
    void printErrors();
};


#endif //LAB3_GOC_LEXER_H
