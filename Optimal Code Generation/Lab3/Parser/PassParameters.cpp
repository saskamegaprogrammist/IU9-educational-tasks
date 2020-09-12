//
// Created by alexis on 07.06.2020.
//

#include "PassParameters.h"

PassParameters::PassParameters(int index, unique_ptr<Node>node) :
    index(index), node(move(node)) {}

