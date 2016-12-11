//
//  ArrayTools.c
//  Equation
//
//  Created by Nick Mittu on 12/10/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include "ArrayTools.h"
#include <stdlib.h>
#include <string.h>
#define FUNC_NAME_SIZE 50

void insert_str(char** array, size_t* size, char* str, int index) {
    for (int i = *size; i > index; i--){
        array[i] = array[i - 1];
    }
    (*size)++;
    array[index] = str;
}

void remove_str_from_array(char** array, int index, int array_length){
    for(int i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}

char** copy_array(char** array, size_t size){
    char** copy = malloc(sizeof(char*)*size);
    for (int i = 0; i<size; i++) {
        copy[i] = malloc(sizeof(char)*FUNC_NAME_SIZE);
        strcpy(copy[i], array[i]);
    }
    return copy;
}
