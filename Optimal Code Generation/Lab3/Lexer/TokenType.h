//
// Created by alexis on 06.06.2020.
//

#ifndef LAB3_GOC_TOKENTYPE_H
#define LAB3_GOC_TOKENTYPE_H

#include <string>
#include <map>

using namespace std;

enum TokenType {
    KEYWORD,
    VALUE_TYPE,
    IDENTIFICATOR,
    OPERATOR,
    LEFT_BR,
    RIGHT_BR,
    SEMICOLON,
    EQ,
    END
};

static map <TokenType, string> tokenTypes = {{KEYWORD, "KEYWORD"}, {VALUE_TYPE, "VALUE"}, {IDENTIFICATOR, "IDENT"},
                                      {OPERATOR,"OP"}, {LEFT_BR, "("}, {RIGHT_BR, ")"}, {SEMICOLON, ";"},
                                             {EQ, "="}, {END, "END"}};

#endif //LAB3_GOC_TOKENTYPE_H
