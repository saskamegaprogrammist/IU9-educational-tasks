//
// Created by alexis on 06.06.2020.
//

#ifndef LAB3_GOC_POSITION_H
#define LAB3_GOC_POSITION_H


#include <string>
using namespace std;
class Position {
private:
    string file;
    int fileLength;
    int index = 0;
    int line = 1;
    int position = 1;
public:
    Position() = default;
    Position(const string &file);
    Position(const Position &position);
    bool isNewline();
    bool isWhiteSpace();
    bool isDigit();
    bool isLetter();
    bool isSmallLetter();
    bool isCapLetter();
    bool isDot();
    bool isEq();
    bool isOp();
    bool isLeftBr();
    bool isRightBr();
    bool isSemiColon();
    void next();
    int getCurrentPosition();
    string getFile() ;
    int getFileLength() ;
    int getIndex() ;
    int getPosition() ;
    int getLine() ;
};


#endif //LAB3_GOC_POSITION_H
