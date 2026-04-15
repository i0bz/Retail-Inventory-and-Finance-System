#include "my_vector.h"
#include "inventory.h"
#include <stdlib.h>
#include <string.h>

static Vector* inventory = NULL;

Product* create_product(unsigned int id, char* name, char* category, float price, size_t quantity) {
    Product* product = malloc(sizeof(Product));
    product->id = id;
    strncpy(product->name, name, PRODUCT_STRING_BUFFER_SIZE);
    strncpy(product->category, category, PRODUCT_STRING_BUFFER_SIZE);
    product->price = price;
    product->quantity = quantity;
    product->sold = 0;

    return product;
}


void open_inventory() {
    if (inventory == NULL) 
        inventory = create_vector(sizeof(Product));
}

void close_inventory() {
    if (inventory != NULL) 
        free(inventory);
}




void add_to_inventory(Product* product) {
    push_to_vector(inventory, product);
}

Product* retrieve_from_inventory(ID id) {
    for (size_t i = 0; i < inventory->usage + 1; i++) {
        Product* product = (Product*) at_vector(inventory, i);
        if (product->id == id) return product;
    }

    return NULL;
}

void remove_from_inventory(ID id) {
    for (size_t i = 0; i < inventory->usage + 1; i++) {
        Product* product = (Product*) at_vector(inventory, i);
        if (product->id == id) remove_from_vector(inventory, i);
    }
}

size_t inventory_usage() {
    return inventory->usage;
}

void for_every_item(void(*func)(void*)) {
    for (size_t i = 0; i < inventory->usage; i++) {
        Product* product = (Product*) at_vector(inventory, i);
        func(product);
    }
}
