//
//  main.c
//  Equation
//
//  Created by Nick Mittu on 12/8/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include <stdio.h>
#include "Equation.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    struct Equation* eq = create_equation("(x+6)(x-7)");
    
    printf("%s\n", eq->equation);
    
    printf("%zul, %zul\n", eq->rev_pol_len, strlen(eq->equation));
    
    for (int i = 0; i < eq->rev_pol_len; i++) {
        printf("%s,", eq->rev_polish[i]);
    }
    
    return 0;
}
