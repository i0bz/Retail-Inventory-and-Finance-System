#ifndef M_HASHMAP_H
#define M_HASHMAP_H


#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_BUCKET_SIZE 1000



typedef struct Node {
    void* key;
    void* data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
} List;

typedef struct Hashmap {
    List buckets[DEFAULT_BUCKET_SIZE];
    size_t bucket_size;
} Hashmap;



Node* create_node(void* key, void* data);

Hashmap* create_hashmap();
void free_hashmap(Hashmap* map);

void push(Hashmap* map, void* key, void* object);
void pop(Hashmap* map , void* key);
void* search(Hashmap* map, void* key);
void foreach(Hashmap* map, void (*func)(void*));




#include "hashmap_functions.h"


#endif