#ifndef PRODUCT_DEF_H
#define PRODUCT_DEF_H

#include <stddef.h>

typedef unsigned int ID;

typedef struct Product {
    ID id;
    char* name;
    char* category;
    float price;
    size_t quantity;
    size_t sold;
} Product;


Product* create_product(unsigned int id, char* name, char* category, float price, size_t quantity);

#endif