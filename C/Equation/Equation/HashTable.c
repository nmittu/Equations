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
    hash->hash_array = malloc(sizeof(struct DataItem*)*size);
    hash->length = 0;
    
    return hash;
}

void hash_insert(struct HashTable* table, char* key, struct Data* data){
    int i = 0;
    while(i < table->size && table->hash_array[i] != NULL){
        i++;
    }
    
    table->hash_array[i] = malloc(sizeof(struct DataItem));
    table->hash_array[i]->data = data;
    table->hash_array[i]->key = key;
    table->hash_array[i]->index = table->length;
    table->length++;
}

struct DataItem* hash_search(struct HashTable* table, char* key){
    for (int i = 0; i<table->size; i++) {
        if(table->hash_array[i] != NULL && strcmp(table->hash_array[i]->key, key) == 0){
            return table->hash_array[i];
        }
    }
    return NULL;
}

struct DataItem* hash_search_i(struct HashTable* table, int index){
    for (int i = 0; i<table->size; i++) {
        if(table->hash_array[i] != NULL && table->hash_array[i]->index == index){
            return table->hash_array[i];
        }
    }
    return NULL;
}

struct DataItem* hash_delete(struct HashTable* table, char* key){
    for (int i = 0; i<table->size; i++) {
        if (table->hash_array[i] != NULL && strcmp(table->hash_array[i]->key, key) == 0) {
            struct DataItem* ret = table->hash_array[i];
            table->hash_array[i] = NULL;
            table->length--;
            return ret;
        }
    }
    return NULL;
}

struct DataItem* hash_delete_i(struct HashTable* table, int index){
    for (int i = 0; i<table->size; i++) {
        if (table->hash_array[i] != NULL && table->hash_array[i]->index == index) {
            struct DataItem* ret = table->hash_array[i];
            table->hash_array[i] = NULL;
            table->length--;
            return ret;
        }
    }
    return NULL;
}
