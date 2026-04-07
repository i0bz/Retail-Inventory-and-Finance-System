#ifndef INVENTORY_H
#define INVENTORY_H

#include "product.h"


void open_inventory();
void close_inventory();

void add_to_inventory(Product* product);
void remove_from_inventory(ID id);
Product* retrieve_from_inventory(ID id);


void for_every_item(void(*func)(void*));


#endif