//
// Created by alexis on 06.06.2020.
//

#include <iostream>
#include "Token.h"

Token:: Token(TokenType type, const string &attribute, const Position & st, const Position & end) :
        type(type), attribute(attribute){
    this->coordinates = Fragment (st, end);
}

void Token::print() {
    cout << "Token " << tokenTypes.find(type)->second << " :" << this->attribute << " at position: ";
    coordinates.print();
    cout << endl;
}

string Token::getAttr() {
    return this->attribute;
}

TokenType Token::getType() {
    return this->type;
}

Fragment Token::getCoords() {
    return this->coordinates;
}