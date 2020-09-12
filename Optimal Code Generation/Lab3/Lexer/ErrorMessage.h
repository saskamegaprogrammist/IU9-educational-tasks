//
// Created by alexis on 07.06.2020.
//

#ifndef LAB3_GOC_ERRORMESSAGE_H
#define LAB3_GOC_ERRORMESSAGE_H


#include <string>
#include "Fragment.h"

using namespace std;

class ErrorMessage {
private:
    string message;
    Fragment coordinates;
public:
    ErrorMessage() = default;
    ErrorMessage(const string &message, const Fragment &coords);
    ErrorMessage(const string &message, const Position &st, const Position &end);
    void print();
};



#endif //LAB3_GOC_ERRORMESSAGE_H
