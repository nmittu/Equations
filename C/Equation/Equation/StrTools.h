//
//  StrTools.h
//  Equation
//
//  Created by Nick Mittu on 12/10/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#ifndef StrTools_h
#define StrTools_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_search(char** source, size_t src_size, char* target);
int str_len_cmp(const void* a, const void* b);
char* str_deblank(char* input);
int str_is_dec(char* str);

#endif /* StrTools_h */
