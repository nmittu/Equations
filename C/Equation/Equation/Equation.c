//
//  Equation.c
//  Equation
//
//  Created by Nick Mittu on 12/8/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include "Equation.h"

void remove_str_from_array(char** array, int index, int array_length){
    free(array[index]);
    for(int i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}

char** split_str(char** dest, char* str, size_t* size){
    for (int i = 0; i<*size; i++) {
        dest[i] = malloc(sizeof(char)*15);
        dest[i][0] = str[i];
        dest[i][1] = '\0';
    }
    
    return dest;
}

char** find_func_tokens(char** array, size_t* size, struct HashTable* table){
    char funcNames[table->length][50];
    
    for (int i = 0; i<table->length; i++) {
        strcpy(funcNames[i], hash_search_i(table, i)->key);
    }
    
    qsort(funcNames, table->length, 50, str_len_cmp);
    
    for (int i = 0; i<table->length; i++) {
        while (str_search(array, *size, funcNames[i]) != -1) {
            int index = str_search(array, *size, funcNames[i]);
            strcpy(array[index], funcNames[i]);
            for (int j = 0; j<strlen(funcNames[i])-1; j++) {
                remove_str_from_array(array, index+1, *size);
                (*size)--;
            }
        }
    }
    
    
    return array;
}

struct Equation* equation_create(char* equation){
    struct Equation* eq = malloc(sizeof(struct Equation));
    eq->equation = str_deblank(equation);
    
    eq->operators = hash_create(8);
    eq->functions = hash_create(500);
    
    struct Data* exp = malloc(sizeof(struct Data));
    exp->precedence = 4;
    exp->associativity = 'R';
    exp->arity = -1;
    exp->callback = NULL;

    struct Data* mult = malloc(sizeof(struct Data));
    mult->precedence = 3;
    mult->associativity = 'L';
    mult->arity = -1;
    mult->callback = NULL;
    
    struct Data* div = malloc(sizeof(struct Data));
    div->precedence = 3;
    div->associativity = 'L';
    div->arity = -1;
    div->callback = NULL;
    
    struct Data* add = malloc(sizeof(struct Data));
    add->precedence = 2;
    add->associativity = 'L';
    add->arity = -1;
    add->callback = NULL;
    
    struct Data* sub = malloc(sizeof(struct Data));
    sub->precedence = 2;
    sub->associativity = 'L';
    sub->arity = -1;
    sub->callback = NULL;
    
    struct Data* neg = malloc(sizeof(struct Data));
    neg->precedence = 6;
    neg->associativity = 'R';
    neg->arity = -1;
    neg->callback = NULL;
    
    struct Data* sqrt = malloc(sizeof(struct Data));
    sqrt->precedence = 4;
    sqrt->associativity = 'R';
    sqrt->arity = -1;
    sqrt->callback = NULL;
    
    struct Data* fact = malloc(sizeof(struct Data));
    fact->precedence = 5;
    fact->associativity = 'R';
    fact->arity = -1;
    fact->callback = NULL;
    
    hash_insert(eq->operators, "^", exp);
    hash_insert(eq->operators, "*", mult);
    hash_insert(eq->operators, "/", div);
    hash_insert(eq->operators, "+", add);
    hash_insert(eq->operators, "-", sub);
    hash_insert(eq->operators, "~", neg);
    hash_insert(eq->operators, "|", sqrt);
    hash_insert(eq->operators, "!", fact);
    
    struct Data* log = malloc(sizeof(struct Data));
    log->arity = 2;
    log->callback = math_log;
    log->precedence = -1;
    log->associativity = '\0';
    
    struct Data* ln = malloc(sizeof(struct Data));
    log->arity = 1;
    log->callback = math_ln;
    log->precedence = -1;
    log->associativity = '\0';
    
    struct Data* abs = malloc(sizeof(struct Data));
    log->arity = 1;
    log->callback = math_abs;
    log->precedence = -1;
    log->associativity = '\0';
    
    struct Data* acos = malloc(sizeof(struct Data));
    log->arity = 1;
    log->callback = math_acos;
    log->precedence = -1;
    log->associativity = '\0';
    
    struct Data* asin = malloc(sizeof(struct Data));
    log->arity = 1;
    log->callback = math_asin;
    log->precedence = -1;
    log->associativity = '\0';
    
    struct Data* atan = malloc(sizeof(struct Data));
    log->arity = 1;
    log->callback = math_atan;
    log->precedence = -1;
    log->associativity = '\0';
    
    struct Data* cos = malloc(sizeof(struct Data));
    log->arity = 1;
    log->callback = math_cos;
    log->precedence = -1;
    log->associativity = '\0';
    
    struct Data* sin = malloc(sizeof(struct Data));
    log->arity = 1;
    log->callback = math_sin;
    log->precedence = -1;
    log->associativity = '\0';
    
    struct Data* tan = malloc(sizeof(struct Data));
    log->arity = 1;
    log->callback = math_tan;
    log->precedence = -1;
    log->associativity = '\0';
    
    hash_insert(eq->functions, "log", log);
    hash_insert(eq->functions, "ln", ln);
    hash_insert(eq->functions, "abs", abs);
    hash_insert(eq->functions, "acos", acos);
    hash_insert(eq->functions, "asin", asin);
    hash_insert(eq->functions, "atan", atan);
    hash_insert(eq->functions, "cos", cos);
    hash_insert(eq->functions, "sin", sin);
    hash_insert(eq->functions, "tan", tan);
    
    eq->rev_polish = (char**) malloc(sizeof(char*)*1000);
    eq->rev_pol_len = strlen(equation);
    eq->rev_polish = find_func_tokens(split_str(eq->rev_polish, eq->equation, &eq->rev_pol_len), &eq->rev_pol_len, eq->functions);
    
    return eq;
}
