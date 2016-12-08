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

struct Equation {
    char** rev_polish;
    char* equation;
    size_t rev_pol_len;
};

struct Equation* create_equation(char* equation);

#endif /* Equation_h */
