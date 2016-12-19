//
//  ArrayTools.h
//  Equation
//
//  Created by Nick Mittu on 12/10/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#ifndef ArrayTools_h
#define ArrayTools_h

#include <stdio.h>

void insert_str(char** array, size_t* size, char* str, int index);
void remove_str_from_array(char** array, int index, int array_length);
char** copy_array(char** array, size_t size);
void free_array(char** array, size_t size);


#endif /* ArrayTools_h */
