//
//  HashTable.h
//  Equation
//
//  Created by Nick Mittu on 12/8/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data{
    int arity;
    long double (*callback)(long double[]);
};

struct DataItem{
    char* key;
    struct Data data;
};

struct HashTable{
    struct DataItem* hash_array;
    size_t size;
};

struct HashTable* hash_create(size_t size);
struct DataItem* hash_search(struct HashTable*, char* key);
void hash_insert(struct HashTable*, char* key, struct Data data);
struct DataItem* hash_delete(struct HashTable*, struct DataItem* item);

#endif /* HashTable_h */
