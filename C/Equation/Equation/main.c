//
//  main.c
//  Equation
//
//  Created by Nick Mittu on 12/8/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include <stdio.h>
#include "Equation.h"
#include "HashTable.h"
#include "StrTools.h"

long double add5(long double args[]){
    return args[0]+args[1]+args[2]+args[3]+args[4];
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    struct Equation* eq = equation_create("add5(1, 2, 3, 4, 5)");
    equation_add_func(eq, "add5", 5, add5);
    
    for (int i = 0; i<eq->rev_pol_len; i++) {
        printf("%s ", eq->rev_polish[i]);
    }
    
    printf("\n");
    printf("%.17Lf\n", equation_solve(eq, 5, "x"));

	

    return 0;
}

