#include "m_hashmap.h"
#include "product.h"

Product* create_product(unsigned int id, char* name, char* category, float price, size_t quantity, size_t sold) {
    Product* product = malloc(sizeof(Product));
    product->id = id;
    product->name = name;
    product->category = category;
    product->price = price;
    product->quantity = quantity;
    product->sold = 0;

    return product;
}