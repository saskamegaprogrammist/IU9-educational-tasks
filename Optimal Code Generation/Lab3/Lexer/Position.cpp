//
// Created by alexis on 06.06.2020.
//

#include "Position.h"

static const int ENDOFFILE = -1;
static const int HT = 9;
static const int LF = 10;
static const int FF = 12;
static const int CR = 13;
static const int SPACE = 32;
static const int LEFTBR = 40;
static const int RIGHTBR = 41;
static const int MUL = 42;
static const int PLUS = 43;
static const int MINUS = 45;
static const int DOT = 46;
static const int DIVIDE = 47;
static const int ZERO = 48;
static const int NINE = 57;
static const int SCOLON = 59;
static const int LESS = 60;
static const int EQ = 61;
static const int MORE = 62;
static const int ACAP = 65;
static const int ZCAP = 90;
static const int ASMALL = 97;
static const int ZSMALL = 122;



Position::Position(const string &file) : file(file) {
    this->fileLength = file.size();
}

Position::Position(Position const &position) {
    this->file = position.file;
    this->fileLength = position.fileLength;
    this->index = position.index;
    this->position = position.position;
    this->line = position.line;
}

string Position::getFile() {
    return this->file;
}

int Position::getFileLength()  {
    return this->fileLength;
}

int Position::getLine() {
    return this->line;
}

int Position::getIndex() {
    return this->index;
}

int Position::getPosition() {
    return this->position;
}

int Position::getCurrentPosition() {
    if (this->index != this->fileLength) {
        return this->file.at(this->index);
    } else {
        return ENDOFFILE;
    }
}


bool Position::isDigit() {
    int currPos = this->getCurrentPosition();
    return  (currPos >=ZERO && currPos<= NINE);
}

bool Position::isWhiteSpace() {
    int currPos = this->getCurrentPosition();
    return  (currPos == SPACE || currPos == HT || currPos == LF ||  currPos == FF || currPos == CR);
}

bool Position::isDot() {
    int currPos = this->getCurrentPosition();
    return  (currPos == DOT);
}


bool Position::isEq() {
    int currPos = this->getCurrentPosition();
    return  (currPos == EQ);
}

bool Position::isOp() {
    int currPos = this->getCurrentPosition();
    return  (currPos == MUL || currPos == DIVIDE || currPos == PLUS || currPos == MINUS
    || currPos == LESS || currPos == MORE);
}

bool Position::isSemiColon() {
    int currPos = this->getCurrentPosition();
    return  (currPos == SCOLON);
}

bool Position::isLeftBr() {
    int currPos = this->getCurrentPosition();
    return  (currPos == LEFTBR);
}

bool Position::isRightBr() {
    int currPos = this->getCurrentPosition();
    return  (currPos == RIGHTBR);
}

bool Position::isSmallLetter() {
    int currPos = this->getCurrentPosition();
    return  (currPos >= ASMALL && currPos <= ZSMALL);
}

bool Position::isCapLetter() {
    int currPos = this->getCurrentPosition();
    return  (currPos >= ACAP && currPos <= ZCAP);
}

bool Position::isLetter() {
    return  (this->isSmallLetter() || this->isCapLetter());
}

bool Position::isNewline() {
    int currPos = this->getCurrentPosition();
    if (currPos == ENDOFFILE) return true;
    if (currPos == LF) return true;
    if (currPos == CR && this->index + 1 < this->fileLength) {
        if (this->file.at(this->index+1) == LF) {
            return true;
        }
    }
    return false;
}

void Position::next() {
    if (this->index < this->getFileLength()) {
        if (this->isNewline()) {
            int currPos = this->getCurrentPosition();
            if (currPos == CR) this->index++;
            this->line++;
            this->position = 1;
        } else {
            this->position++;
        }
        this->index++;
    }
}