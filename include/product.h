#ifndef PRODUCT_DEF_H
#define PRODUCT_DEF_H

#include <stddef.h>

typedef unsigned long long ID;

#define PRODUCT_STRING_BUFFER_SIZE 25

typedef struct Product {
    ID id;
    char name[PRODUCT_STRING_BUFFER_SIZE];
    char category[PRODUCT_STRING_BUFFER_SIZE];
    float price;
    size_t quantity;
    size_t sold;
} Product;



Product* create_product(unsigned int id, char* name, char* category, float price, size_t quantity);


#endif