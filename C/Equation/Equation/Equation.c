//
//  Equation.c
//  Equation
//
//  Created by Nick Mittu on 12/8/16.
//  Copyright © 2016 MittuDev. All rights reserved.
//

#include "Equation.h"
#include "MathDef.h"
#include "StrTools.h"
#define FUNC_NAME_SIZE 50

void insert_str(char** array, size_t* size, char* str, int index) {
	for (int i = *size; i > index; i--){
		array[i] = array[i - 1];
	}
	(*size)++;
	array[index] = str;
}

void remove_str_from_array(char** array, int index, int array_length){
    free(array[index]);
    for(int i = index; i < array_length - 1; i++) array[i] = array[i + 1];
}

char** split_str(char** dest, char* str, size_t* size){
    for (int i = 0; i<*size; i++) {
        dest[i] = malloc(sizeof(char)*FUNC_NAME_SIZE);
        dest[i][0] = str[i];
        dest[i][1] = '\0';
    }
	if (strcmp(dest[*size - 1], "\0") == 0) {
		free(dest[*size - 1]);
		dest[*size - 1] = NULL;
		(*size)--;
	}
    
    return dest;
}

char** find_func_tokens(char** array, size_t* size, struct HashTable* table){
    char** funcNames = malloc(sizeof(char*)*table->length);

    for (int i = 0; i<table->length; i++) {
		funcNames[i] = malloc(sizeof(char) * FUNC_NAME_SIZE);
        strcpy(funcNames[i], hash_search_i(table, i)->key);
    }
    
    qsort(funcNames, table->length, sizeof(char*), str_len_cmp);
    
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

char** combine_nums(char** array, size_t* size) {
	char** out = malloc(sizeof(char*)*1000);
	size_t out_len = 0;
	for (int i = 0; i < *size; i++){
		if (out_len) {
			if (str_is_dec(array[i]) && str_is_dec(out[out_len-1])) {
				strcat(out[out_len - 1], array[i]);
				free(array[i]);
			}else{
				out[out_len] = array[i];
				out_len++;
			}
		}else{
			out[out_len] = array[i];
			out_len++;
		}
	}

	*size = out_len;
	return out;
}

char** convert_negatives(char** array, size_t* size, struct HashTable* table) {
	for (int i = 0; i < *size; i++){
		if (strcmp(array[i], "-") == 0) {
			if (i - 1 < 0 || hash_search(table, array[i - 1]) != NULL || strcmp(array[i - 1], "(") == 0) {
				free(array[i]);
				array[i] = "~";
			}
		}
	}

	return array;
}

char** fix_paren_mult(char** array, size_t* size, struct HashTable* operators, struct HashTable* functions) {
	for (int i = 0; i < *size; i++) {
		if (strcmp(array[i], "(") == 0) {
			if (i - 1 >= 0 && hash_search(operators, array[i - 1]) == NULL && hash_search(functions, array[i - 1]) == NULL && strcmp(array[i - 1], ",") != 0) {
				insert_str(array, size, "*", i);
			}
		}else if (strcmp(array[i], ")") == 0){
			if (i + 1 < *size && hash_search(operators, array[i + 1]) == NULL && hash_search(functions, array[i + 1]) == NULL && strcmp(array[i + 1], ",") != 0 && strcmp(array[i + 1], ")") != 0) {
				insert_str(array, size, "*", i+1);
			}
		}
	}

	return array;
}

char** fix_var_mult(char** array, size_t* size, struct HashTable* operators, struct HashTable* functions) {
	for (int i = 0; i < *size; i++){
		if (hash_search(operators, array[i]) == NULL && !str_is_dec(array[i]) && strcmp(array[i], "(") != 0 && strcmp(array[i], ")") != 0 && strcmp(array[i], ",") != 0) {
			if (i - 1 >= 0 && hash_search(operators, array[i - 1]) == NULL && hash_search(functions, array[i - 1]) == NULL && strcmp(array[i - 1], "(") != 0 && strcmp(array[i - 1], ")") != 0 && strcmp(array[i - 1], ",") != 0) {
				insert_str(array, size, "*", i);
				i--;
			}
		}
	}

	return array;
}

void shunt(struct Equation* eq) {
	char** equation = eq->rev_polish;
	int equation_len = eq->rev_pol_len;

	char** opp_stack = malloc(sizeof(char*)*eq->rev_pol_len);
	int opp_stack_len = 0;
	eq->rev_polish = malloc(sizeof(char*)*eq->rev_pol_len);
	eq->rev_pol_len = 0;

	for (int i = 0; i < equation_len; i++){
		if (hash_search(eq->operators, equation[i]) == NULL && hash_search(eq->functions, equation[i]) == NULL && strcmp(equation[i], "(") != 0 && strcmp(equation[i], ")") != 0 && strcmp(equation[i], ",") != 0) {
			eq->rev_polish[eq->rev_pol_len] = equation[i];
			eq->rev_pol_len++;
		}else if (hash_search(eq->functions, equation[i]) != NULL) {
			opp_stack[opp_stack_len] = equation[i];
			opp_stack_len++;
		}else if (strcmp(equation[i], ",") == 0) {
			while (opp_stack_len && strcmp(opp_stack[opp_stack_len-1], "(") != 0){
				eq->rev_polish[eq->rev_pol_len] = opp_stack[opp_stack_len-1];
				opp_stack[opp_stack_len - 1] = NULL;
				eq->rev_pol_len++;
				opp_stack_len--;
			}
		}else if (hash_search(eq->operators, equation[i]) != NULL) {
			while (opp_stack_len && hash_search(eq->operators, opp_stack[opp_stack_len - 1]) != NULL && ((hash_search(eq->operators, equation[i])->data->associativity == 'L' && hash_search(eq->operators, equation[i])->data->precedence <= hash_search(eq->operators, opp_stack[opp_stack_len-1])->data->precedence) || (hash_search(eq->operators, equation[i])->data->associativity == 'R' && hash_search(eq->operators, equation[i])->data->precedence < hash_search(eq->operators, opp_stack[opp_stack_len-1])->data->precedence))) {
				eq->rev_polish[eq->rev_pol_len] = opp_stack[opp_stack_len - 1];
				opp_stack[opp_stack_len - 1] = NULL;
				eq->rev_pol_len++;
				opp_stack_len--;
			}
			opp_stack[opp_stack_len] = equation[i];
			opp_stack_len++;
		}else if (strcmp(equation[i], "(") == 0) {
			opp_stack[opp_stack_len] = equation[i];
			opp_stack_len++;
		}else if (strcmp(equation[i], ")") == 0) {
			while (opp_stack_len && strcmp(opp_stack[opp_stack_len-1], "(") != 0){
				eq->rev_polish[eq->rev_pol_len] = opp_stack[opp_stack_len - 1];
				opp_stack[opp_stack_len-1] = NULL;
				eq->rev_pol_len++;
				opp_stack_len--;
			}
			if (opp_stack_len) {
				free(opp_stack[opp_stack_len - 1]);
				opp_stack[opp_stack_len - 1] = NULL;
				opp_stack_len--;
			}
			if (opp_stack_len && hash_search(eq->functions, opp_stack[opp_stack_len - 1]) != NULL) {
				eq->rev_polish[eq->rev_pol_len] = opp_stack[opp_stack_len - 1];
				opp_stack[opp_stack_len - 1] = NULL;
				opp_stack_len--;
				eq->rev_pol_len++;
			}
		}
	}

	while (opp_stack_len){
		eq->rev_polish[eq->rev_pol_len] = opp_stack[opp_stack_len - 1];
		opp_stack[opp_stack_len - 1] = NULL;
		opp_stack_len--;
		eq->rev_pol_len++;
	}

	free(equation);
	free(opp_stack);
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
	
    eq->rev_polish = fix_var_mult(fix_paren_mult(convert_negatives(combine_nums(find_func_tokens(split_str(eq->rev_polish, eq->equation, &eq->rev_pol_len), &eq->rev_pol_len, eq->functions), &eq->rev_pol_len), &eq->rev_pol_len, eq->operators), &eq->rev_pol_len, eq->operators, eq->functions), &eq->rev_pol_len, eq->operators, eq->functions);
    
	shunt(eq);

    return eq;
}
