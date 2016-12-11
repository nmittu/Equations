//
//  Equation.h
//  Equation
//
//  Created by Nick Mittu on 12/8/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#ifndef Equation_h
#define Equation_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"


struct Equation {
    struct HashTable* operators;
    struct HashTable* functions;
    char** rev_polish;
    char* equation;
    size_t rev_pol_len;
};

struct Equation* equation_create(char* equation);

#endif /* Equation_h */
