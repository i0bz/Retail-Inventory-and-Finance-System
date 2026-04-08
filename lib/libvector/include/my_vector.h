#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Vector {
    void* data;
    size_t element_size;
    size_t capacity;
    size_t usage;
} Vector;

bool search_comparator(void* x, void* y);


Vector* create_vector(size_t element_size);
void push_to_vector(Vector* container, void* object);
void remove_from_vector(Vector* container, size_t index);
void* search_in_vector(Vector* container, void* key);
void foreach_vector_element(Vector* container, void (*func)(void*));

#endif