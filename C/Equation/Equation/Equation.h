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
long double equation_solve(struct Equation* eq, long double var_val, char* var_name);
void equation_add_func(struct Equation* eq, char* name, int arity, long double (*callback)(long double[]));
int equation_is_equal(struct Equation* eq1, struct Equation* eq2);
void equation_destroy(struct Equation* eq);

#endif /* Equation_h */
