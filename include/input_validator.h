#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

int integer_input();
float float_input();
char* string_input();
unsigned long long positive_integer_input();
float positive_float_input();


#endif