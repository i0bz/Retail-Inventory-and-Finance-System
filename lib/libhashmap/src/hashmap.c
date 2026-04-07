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
    
    if(list->head == NULL) {
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
    if (compare_keys(key, iterating_node->key)) return iterating_node->data;

    while (iterating_node != NULL) {
        if (compare_keys(key, iterating_node->key)) return iterating_node->data;
        iterating_node = iterating_node->next;
    }

    return NULL;
}
void remove(Hashmap* map , void* key) {
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
        return;
    }

    if (fast == list->tail) {
        if (!compare_keys(key, fast->key)) return;
    }
    
    slow->next = fast->next;
    free(fast);
}


void foreach(Hashmap* map, void (*func)(void*)) {
    for (size_t i = 0; i < map->bucket_size; i++) {
        if (map->buckets[i].head == NULL) continue;
        List* list = &map->buckets[i];
        Node* iterator = list->head;
        while (iterator != NULL) {
            func(iterator->data);
            iterator = iterator->next;
        }
    }
}
