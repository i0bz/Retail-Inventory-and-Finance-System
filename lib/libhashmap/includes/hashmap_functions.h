#ifndef HASHMAP_FUNCTIONS_H
#define HASHMAP_FUNCTIONS_H

#include "m_hashmap.h"

bool compare_keys (void* key_1, void* key_2);
size_t hash_function(Hashmap* map, void* key);


#endif