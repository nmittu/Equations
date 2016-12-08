//
//  Equation.c
//  Equation
//
//  Created by Nick Mittu on 12/8/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include "Equation.h"

char** split_str(char** dest, char* str, size_t* size){
    for (int i = 0; i<*size; i++) {
        dest[i] = malloc(sizeof(char)*15);
        dest[i][0] = str[i];
        dest[i][1] = '\0';
    }
    
    return dest;
}

struct Equation* create_equation(char* equation){
    struct Equation* eq = malloc(sizeof(struct Equation));
    eq->equation = equation;
    
    eq->rev_polish = (char**) malloc(sizeof(char*)*1000);
    eq->rev_pol_len = strlen(equation);
    
    eq->rev_polish = split_str(eq->rev_polish, eq->equation, &eq->rev_pol_len);
    
    return eq;
}
