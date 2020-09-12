//
// Created by alexis on 07.06.2020.
//

#include <iostream>
#include "ErrorMessage.h"

ErrorMessage:: ErrorMessage(const string &message, const Position &st, const Position &end) :
        message(message){
    coordinates = Fragment(st, end);
}

ErrorMessage:: ErrorMessage(const string &message, const Fragment &coords) :
        message(message), coordinates(coords){}

void ErrorMessage::print() {
    cout << "Error :" << this->message << " at position: ";
    coordinates.print();
    cout << endl;
}