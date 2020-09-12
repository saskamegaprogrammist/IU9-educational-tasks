//
// Created by alexis on 06.06.2020.
//

#include <iostream>
#include "Lexer.h"

static const int ENDOFFILE = -1;


Lexer::Lexer(const string &file) : file(file) {
    this->position = Position(this->file);
}

vector<Token> Lexer::getTokenSet() {
    if (this->tokens.empty()) {
        this->lex();
    }
    return this->tokens;
}

vector<ErrorMessage> Lexer::getErrors() {
    if (this->errors.empty()) {
        this->lex();
    }
    return this->errors;
}

void Lexer::printTokens() {
    if (this->tokens.empty()) {
        this->lex();
    }
    for (int i=0; i<tokens.size(); i++) {
        tokens.at(i).print();
    }
}

void Lexer::printErrors() {
    if (!this->errors.empty()) {
        for (int i = 0; i < errors.size(); i++) {
            errors.at(i).print();
        }
    }
}

void Lexer::lex() {
    int bracketsOpened = 0;
    TokenType lastToken = (TokenType) ENDOFFILE;
    while (this->position.getCurrentPosition() != ENDOFFILE) {
        while (this->position.isWhiteSpace()) this->position.next();
        Position start = Position(position);
        if (this->position.isLeftBr()) {
            bracketsOpened++;
            this->position.next();
            this->tokens.emplace_back(LEFT_BR, this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex()),
                    start, this->position);
            lastToken = LEFT_BR;
            continue;
        }
        if (this->position.isRightBr()) {
            if (bracketsOpened == 0) {
                this->errors.emplace_back(ErrorMessage(string("Right bracket is not allowed here"),
                        start, this->position));
            }
            bracketsOpened--;
            this->position.next();
            this->tokens.emplace_back(RIGHT_BR, this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex()),
                                      start, this->position);
            lastToken = RIGHT_BR;
            continue;
        }
        if (this->position.isEq()) {
            if (lastToken != VALUE_TYPE && lastToken != IDENTIFICATOR) {
                this->errors.emplace_back(ErrorMessage(string("Assign is not allowed here"),
                                                       start, this->position));
            }
            this->position.next();
            if (this->position.isEq()) {
                this->position.next();
                this->tokens.emplace_back(OPERATOR, this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex()),
                                          start, this->position);
                lastToken = OPERATOR;
                continue;
            } else {
                this->tokens.emplace_back(EQ, this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex()),
                                          start, this->position);
                lastToken = EQ;
                continue;
            }
        }
        if (this->position.isOp() || this->position.isDot()) {
            if (lastToken == OPERATOR) {
                this->errors.emplace_back(ErrorMessage(string("Operator is not allowed here"),
                                                       start, this->position));
            }
            this->position.next();
            if (this->position.isOp() || this->position.isEq()) {
                string op = this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex() + 1);
                if (op == "++" || op == "--" || op == ">=" || op == "<=") {
                    this->position.next();
                } else {
                    this->errors.emplace_back(ErrorMessage(string("Wrong symbol"), start, this->position));
                }
            }
            this->tokens.emplace_back(OPERATOR, this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex()),
                                      start, this->position);
            lastToken = OPERATOR;
            continue;
        }
        if (this->position.isSemiColon()) {
            if (lastToken == SEMICOLON || lastToken == OPERATOR) {
                this->errors.emplace_back(ErrorMessage(string("Semicolon is not allowed here"),
                                                       start, this->position));
            }
            this->position.next();
            this->tokens.emplace_back(SEMICOLON, this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex()),
                                      start, this->position);
            lastToken = SEMICOLON;
            continue;
        }
        if (this->position.isDigit()) {
            if (lastToken == VALUE_TYPE) {
                this->errors.emplace_back(ErrorMessage(string("Value is not allowed here"),
                                                       start, this->position));
            }
            this->position.next();
            while (this->position.isDigit()) this->position.next();
            this->tokens.emplace_back(VALUE_TYPE, this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex()),
                                      start, this->position);
            lastToken = VALUE_TYPE;
            continue;
        }
        if (this->position.isLetter()) {
            bool keyWordBool = false;
            if (this->position.getCurrentPosition() == 'w') {
                this->position.next();
                while (this->position.isSmallLetter()) this->position.next();
                string keyWord = this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex());
                if (keyWord == "while") {
                    keyWordBool = true;
                }
            }
            if (this->position.getCurrentPosition() == 'i') {
                this->position.next();
                while (this->position.isSmallLetter()) this->position.next();
                string keyWord = this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex());
                if (keyWord == "if") {
                    keyWordBool = true;

                }
            }
            if (this->position.getCurrentPosition() == 't') {
                this->position.next();
                while (this->position.isSmallLetter()) this->position.next();
                string keyWord = this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex());
                if (keyWord == "then") {
                    keyWordBool = true;

                }
            }
            if (this->position.getCurrentPosition() == 'e') {
                this->position.next();
                while (this->position.isSmallLetter()) this->position.next();
                string keyWord = this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex());
                if (keyWord == "else") {
                    keyWordBool = true;

                }
            }
            if (this->position.getCurrentPosition() == 'r') {
                this->position.next();
                while (this->position.isSmallLetter()) this->position.next();
                string keyWord = this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex());
                if (keyWord == "return") {
                    keyWordBool = true;
                }
            }
            if (keyWordBool) {
                this->tokens.emplace_back(KEYWORD, this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex()),
                                          start, this->position);
                lastToken = KEYWORD;
                continue;
            }
            while (this->position.isDigit() || this->position.isLetter()) this->position.next();
            this->tokens.emplace_back(IDENTIFICATOR, this->file.substr (start.getIndex(), this->position.getIndex() - start.getIndex()),
                                      start, this->position);
            lastToken = IDENTIFICATOR;
            continue;
        }
        this->errors.emplace_back(ErrorMessage(string("Wrong symbol"),
                                               start, this->position));
        this->position.next();
    }
    if (bracketsOpened != 0) {
        this->errors.emplace_back(ErrorMessage(string("Expected right bracket"),
                                               this->position, this->position));
    }
    this->tokens.emplace_back(END, "END",
                              this->position, this->position);
}