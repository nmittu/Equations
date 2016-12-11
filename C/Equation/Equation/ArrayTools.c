//
//  ArrayTools.c
//  Equation
//
//  Created by Nick Mittu on 12/10/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include "ArrayTools.h"
#include <stdlib.h>

void insert_str(char** array, size_t* size, char* str, int index) {
    for (int i = *size; i > index; i--){
        array[i] = array[i - 1];
    }
    (*size)++;
    array[index] = str;
}

void remove_str_from_array(char** array, int index, int array_length){
    free(array[index]);
    for(int i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}
