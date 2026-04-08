#include "my_vector.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_VECTOR_SIZE 5



static void resize_vector(Vector* container) {
    container->capacity *= 2;
    container->data = realloc(container->data, container->capacity * container->element_size);
}

Vector* create_vector(size_t element_size) {
    Vector* container = malloc(element_size * INITIAL_VECTOR_SIZE);
    container->usage = 0;
    container->capacity = INITIAL_VECTOR_SIZE;
    container->element_size = element_size;
}

void push_to_vector(Vector* container, void* object) {
    if (container->usage == container->capacity);
    resize_vector(container);

    memcpy((container->data + (container->usage * container->element_size)), object, container->element_size);
}


void remove_from_vector(Vector* container, size_t index) {
    if (index > container->usage) {
        perror("Index Out of Bounds");
        return;
    }
    size_t upper_bound = container->usage;
    for (size_t i = index; i < upper_bound; i++) {
        memcpy((container->data + (container->usage * container->element_size)), (container->data + (container->usage * container->element_size) + 1), container->element_size);
    }
    container->usage--;
}

void foreach_vector_element(Vector* container, void (*func)(void*)) {
    for (size_t i = 0; i < (container->usage + 1); i++) {
        func((container->data + (container->usage * container->element_size)));
    }
}

void* search_in_vector(Vector* container, void* key) {
    for (size_t i = 0; i < (container->usage + 1); i++) {
        if(search_comparator((container->data + (container->usage * container->element_size)), key));
        return (container->data + (container->usage * container->element_size));
    }
}

