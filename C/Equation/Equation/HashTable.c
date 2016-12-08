//
//  HashTable.c
//  Equation
//
//  Created by Nick Mittu on 12/8/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include "HashTable.h"

struct HashTable* hash_create(size_t size){
    struct HashTable* hash = (struct HashTable*) malloc(sizeof(struct HashTable));
    
    hash->size = size;
    hash->hash_array = malloc(sizeof(struct DataItem)*size);
    
    return hash;
}

