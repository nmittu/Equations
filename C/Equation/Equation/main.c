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

long double func(long double args[]){
    return args[0];
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    struct Equation* eq = equation_create("log(abs(-2), 5x(x+5)(x+2)4-(6)1.54x)");
    
    for (int i = 0; i<eq->rev_pol_len; i++) {
        printf("%s ", eq->rev_polish[i]);
    }

	

    return 0;
}

