//
// Created by alexis on 06.06.2020.
//

#include <iostream>
#include <fstream>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

using namespace std;

const string FILENAME = "../file.txt";
const string EMPTY = "";

string readFile() {
    ifstream f(FILENAME);
    if (f) {
        f.seekg(0, ios::end);
        const auto size = f.tellg();
        string str(size, ' ');
        f.seekg(0);
        f.read(&str[0], size);
        f.close();
        return str;
    } else return EMPTY;
}



int main() {
    string file = readFile();
    Lexer lexer = Lexer(file);
//    lexer.printTokens();
    lexer.printErrors();
    Parser parser = Parser(lexer.getTokenSet());
    parser.generateCode();
    parser.printErrors();
    return 0;
}
