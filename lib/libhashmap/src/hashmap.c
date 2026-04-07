#include "m_hashmap.h"

Node* create_node(void* key, void* data) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->key = key;
    node->next = NULL;
    return node;
}


Hashmap* create_hashmap() {
    Hashmap* map = calloc(1, sizeof(Hashmap));
    map->bucket_size = DEFAULT_BUCKET_SIZE;
    return map;
}
void free_hashmap(Hashmap* map) {
    free(map);
}


void push(Hashmap* map, void* key, void* object) {
    size_t bucket_index = hash_function(map, key);

    List* list = &map->buckets[bucket_index];
    Node* node = create_node(key, object);
    
    if(list == NULL) {
        list->head = node;
        list->tail = node;
        return;
    }
    
    Node* iterating_node = list->head;
    
    while (iterating_node != list->tail) {
        if (compare_keys(key, iterating_node->key)) return;
        iterating_node = iterating_node->next;
    }

    list->tail->next = node;
    list->tail = node;
}
void* search(Hashmap* map, void* key) {
    size_t bucket_index = hash_function(map, key);
    
    List* list = &map->buckets[bucket_index];
    
    if (list == NULL) return NULL;
    
    Node* iterating_node = list->head;

    while (iterating_node != list->tail) {
        if (compare_keys(key, iterating_node->key)) return iterating_node->data;
        iterating_node = iterating_node->next;
    }

    return NULL;
}
void remove(Hashmap* map , void* key) {
    size_t bucket_index = hash_function(map, key);

    List* list = &map->buckets[bucket_index];
    
    if (list == NULL) return;
    
    Node* slow = NULL;
    Node* fast = list->head;
    
    while (fast != list->tail) {
        if (compare_keys(key, fast->key)) break;
        slow = fast;
        fast = fast->next;
    }

    
    if (fast == list->head) {
        list->head = NULL;
        list->tail = NULL;
        free(fast);
        return;
    }

    if (fast == list->tail) {
        if (!compare_keys(key, fast->key)) return;
    }
    
    slow->next = fast->next;
    free(fast);
}


void foreach(Hashmap* map, void (*func)());
