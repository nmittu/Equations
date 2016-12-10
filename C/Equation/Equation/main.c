//
//  main.c
//  Equation
//
//  Created by Nick Mittu on 12/8/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include <stdio.h>
#include "Equation.h"
#include "HashTable.h"

long double func(long double args[]){
    return args[0];
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    struct Data* d1 = malloc(sizeof(struct Data));
    struct Data* d2 = malloc(sizeof(struct Data));
    struct Data* d3 = malloc(sizeof(struct Data));
    struct Data* d4 = malloc(sizeof(struct Data));
    
    d1->arity = 1;
    d1->callback = func;
    
    d2->arity = 2;
    d2->callback = func;
    
    d3->arity = 3;
    d3->callback = func;
    
    d4->arity = 4;
    d4->callback = func;
    
    
    
    struct HashTable* table = hash_create(50);
    hash_insert(table, "first", d1);
    hash_insert(table, "second", d2);
    hash_insert(table, "third", d3);
    hash_insert(table, "fourth", d4);
    
    
    long double arg[] =  {0.3, 0.5};
    
    for (int i = 0; i<table->length; i++) {
        printf("%s, %i\n", hash_search_i(table, i)->key, hash_search_i(table, i)->index);
        printf("%Lf\n\n", hash_search_i(table, i)->data->callback(arg));
    }
    
    printf("----------\n");
    
    hash_delete(table, "third");
    hash_delete_i(table, 1);
    
    
    for (int i = 0; i<table->length; i++) {
        printf("%s, %i\n", hash_search_i(table, i)->key, hash_search_i(table, i)->index);
        printf("%Lf\n\n", hash_search_i(table, i)->data->callback(arg));
    }
    
    return 0;
}

