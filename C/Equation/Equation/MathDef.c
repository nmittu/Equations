//
//  MathDef.c
//  Equation
//
//  Created by Nick Mittu on 12/10/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include "MathDef.h"
#include <math.h>

long double math_log(long double args[]){
    return log(args[1])/log(args[0]);
}

long double math_ln(long double args[]){
    return log(args[0]);
}

long double math_abs(long double args[]){
    if (args[0] < 0)
        return -args[0];
    return args[0];
}

long double math_acos(long double args[]){
    return acos(args[0]);
}

long double math_asin(long double args[]){
    return asin(args[0]);
}

long double math_atan(long double args[]){
    return atan(args[0]);
}

long double math_cos(long double args[]){
    return cos(args[0]);
}

long double math_sin(long double args[]){
    return sin(args[0]);
}

long double math_tan(long double args[]){
    return tan(args[0]);
}
