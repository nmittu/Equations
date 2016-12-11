//
//  StrTools.c
//  Equation
//
//  Created by Nick Mittu on 12/10/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "StrTools.h"


int str_search(char** source, size_t src_size, char* target){
    int m = src_size;
    int n = strlen(target);
    int end = m;
    
    if(n == 0 || end < n)
        return -1;
    
    for (int i = 0; i < end-n+1; i++) {
        char* str_found = malloc(sizeof(char)*50);
		strcpy(str_found, "");
        for (int j = 0; j < n; j++) {
            strcat(str_found, source[i+j]);
        }
        if (strcmp(str_found, target) == 0) {
            return i;
        }
    }
        
    
    return -1;
}

int str_len_cmp(const void* a, const void* b){
    size_t fa = strlen(*((char **)a));
    size_t fb = strlen(*((char **)b));
    return (fa < fb) - (fa > fb);
}

char* str_deblank(char* input){
    int i,j;
    char *output=malloc(sizeof(char)*(strlen(input)+1));
    for (i = 0, j = 0; i<strlen(input); i++,j++)
    {
        if (input[i]!=' ')
            output[j]=input[i];
        else
            j--;
    }
    output[j]=0;
    return output;
}

int str_is_dec(char* str) {
	int is_dec = 1;
	int i = 0;
	int dec_count = 0;
	while (str[i] != '\0') {
		if (!(isdigit(str[i]) || str[i] == '.')) {
			is_dec = 0;
		}
		if (str[i] == '.') {
			if (dec_count >= 1) {
				is_dec = 0;
			}
			dec_count++;
		}
		i++;
	}

	return is_dec;
}
