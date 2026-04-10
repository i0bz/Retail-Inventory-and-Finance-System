#include "my_vector.h"
#include "inventory.h"

bool search_comparator(void* x, void* y) {
    return ((Product*)x)->id == ((Product*)y)->id;
}


static Vector* container = NULL;

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
    if (container != NULL) 
        create_vector(sizeof(Product));
}

void close_inventory() {
    if (container != NULL) 
        free(container);
}




void add_to_inventory(Product* product) {
    push_to_vector(container, product);
}

Product* retrieve_from_inventory(ID id) {
    return search_in_vector(container, id);
}

void remove_from_inventory(ID id) {
    


}


Product* retrieve_from_inventory(ID id);
size_t inventory_usage();

void for_every_item(void(*func)(void*));
