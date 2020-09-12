//
// Created by alexis on 06.06.2020.
//

#ifndef LAB3_GOC_TOKEN_H
#define LAB3_GOC_TOKEN_H


#include <string>
#include "TokenType.h"
#include "Fragment.h"
using namespace std;

class Token {
private:
    TokenType type;
    string attribute;
    Fragment coordinates;
public:
    Token() = default;
    Token(TokenType type, const string &data, const Position &st, const Position &end);
    void print();
    string getAttr();
    TokenType getType();
    Fragment getCoords();
};


#endif //LAB3_GOC_TOKEN_H
