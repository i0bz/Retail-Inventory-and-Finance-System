#include "m_hashmap.h"
#include "inventory.h"

static Hashmap* inventory = NULL;

//HASHMAP INTERFACE FUNCTION IMPLEMENTATIONS
//Need to declare since i made a generic hashmap
size_t hash_function(Hashmap* map, void* key) {
    return (*(ID*)key) % map->bucket_size;
}
bool compare_keys (void* key_1, void* key_2) {
    return *(ID*)key_1 == *(ID*)key_2;
}




void for_every_item(void(*func)(void*)) {
    foreach(inventory, func);
}

void open_inventory() {
    if (inventory != NULL) return;
    inventory = create_hashmap();
}
void close_inventory() {
    if (inventory == NULL) return;
    free(inventory);
}

Product* create_product(unsigned int id, char* name, char* category, float price, size_t quantity) {
    Product* product = malloc(sizeof(Product));
    product->id = id;
    product->name = name;
    product->category = category;
    product->price = price;
    product->quantity = quantity;
    product->sold = 0;

    return product;
}

void add_to_inventory(Product* product) {
    push(inventory, (void*)(&product->id), product);
}
void remove_from_inventory(ID id) {
    pop(inventory, (void*)&id);
}
Product* retrieve_from_inventory(ID id) {
    return search(inventory, (void*)&id);
}
