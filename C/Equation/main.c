//
//  main.c
//  Equation
//
//  Created by Nick Mittu on 12/8/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "Equation.h"
#include "HashTable.h"
#include "StrTools.h"

long double atan2_func(long double args[]){
    return atan2(args[0], args[1]);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    struct Equation* eq = equation_create("atan2(3x, log(2, x^2))");
    equation_add_func(eq, "atan2", 2, atan2_func);
    printf("%.17Lf", equation_solve(eq, 25, "x"));

    equation_destroy(eq);

    return 0;
}

