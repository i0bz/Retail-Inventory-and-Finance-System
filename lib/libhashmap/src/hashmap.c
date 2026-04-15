#include "m_hashmap.h"
#include <stdio.h>
#include <stdlib.h>

Node* create_node(void* key, void* data);

Node* create_node(void* key, void* data) {
    Node* node = malloc(sizeof(Node));

    if (node == NULL) return NULL;

    node->data = data;
    node->key = key;
    node->next = NULL;
    return node;
}


Hashmap* create_hashmap() {
    Hashmap* map = calloc(1, sizeof(Hashmap));
    
    if (map == NULL) return NULL;

    map->bucket_size = DEFAULT_BUCKET_SIZE;
    return map;
}

void free_hashmap(Hashmap* map) {
    for (size_t i = 0; i < map->bucket_size; i++) {
        if (map->buckets[i].head == NULL) continue;
        List* list = &map->buckets[i];
        Node* fast = list->head;
        Node* slow = NULL;

        while (fast != NULL) {
            slow = fast;
            fast = fast->next;
            free(slow);
        }
    }



    free(map);
}


void push(Hashmap* map, void* key, void* object) {
    size_t bucket_index = hash_function(map, key);

    List* list = &map->buckets[bucket_index];
    Node* node = create_node(key, object);

    if (node == NULL) {
        perror("Could not allocate a node!!!");
        return;
    }
    
    if(list->head == NULL) {
        list->head = node;
        list->tail = node;
        map->usage++;
        return;
    }
    
    Node* iterating_node = list->head;
    
    while (iterating_node != list->tail) {
        if (compare_keys(key, iterating_node->key)) return;
        iterating_node = iterating_node->next;
    }

    list->tail->next = node;
    list->tail = node;
    map->usage++;
}
void* search(Hashmap* map, void* key) {
    size_t bucket_index = hash_function(map, key);
    
    List* list = &map->buckets[bucket_index];
    
    if (list->head == NULL) return NULL;
    
    Node* iterating_node = list->head;
    if (compare_keys(key, iterating_node->key)) return iterating_node->data;

    while (iterating_node != NULL) {
        if (compare_keys(key, iterating_node->key)) return iterating_node->data;
        iterating_node = iterating_node->next;
    }

    return NULL;
}
void pop(Hashmap* map , void* key) {
    size_t bucket_index = hash_function(map, key);

    List* list = &map->buckets[bucket_index];
    
    if (list->head == NULL) return;
    
    Node* slow = NULL;
    Node* fast = list->head;
    
    while (fast != list->tail) {
        if (compare_keys(key, fast->key)) break;
        slow = fast;
        fast = fast->next;
    }

    
    if (fast == list->head) {
        list->head = list->head->next;
        free(fast);
        map->usage++;
        return;
    }

    if (fast == list->tail) {
        if (!compare_keys(key, fast->key)) return;
    }
    
    slow->next = fast->next;
    free(fast);
    map->usage--;
}


void foreach(Hashmap* map, void (*func)(void*)) {

    size_t amount = 0;
    for (size_t i = 0; i < map->bucket_size; i++) {
        if (amount == map->usage) return;
        if (map->buckets[i].head == NULL) continue;
        List* list = &map->buckets[i];
        Node* iterator = list->head;
        while (iterator != NULL) {
            func(iterator->data);
            amount++;
            iterator = iterator->next;
        }
    }
}
