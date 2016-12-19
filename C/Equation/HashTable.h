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
    int precedence;
    char associativity;
    long double (*callback)(long double[]);
};

struct DataItem{
    char* key;
    int index;
    struct Data* data;
};

struct HashTable{
    struct DataItem** hash_array;
    size_t size;
    int length;
};

struct HashTable* hash_create(size_t size);
struct DataItem* hash_search(struct HashTable* table, char* key);
struct DataItem* hash_search_i(struct HashTable* table, int index);
void hash_insert(struct HashTable* table, char* key, struct Data* data);
struct DataItem* hash_delete(struct HashTable* table, char* key);
struct DataItem* hash_delete_i(struct HashTable* table, int index);
void hash_destroy(struct HashTable* table);


#endif /* HashTable_h */
