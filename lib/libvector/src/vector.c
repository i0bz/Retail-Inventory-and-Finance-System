#include "my_vector.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_VECTOR_SIZE 5
#define BYTE char



static void resize_vector(Vector* container) {
    container->capacity *= 2;
    container->data = realloc(container->data, container->capacity * container->element_size);
}

Vector* create_vector(size_t element_size) {
    Vector* container = malloc(sizeof(Vector));
    container->data = malloc(element_size * INITIAL_VECTOR_SIZE);
    container->usage = 0;
    container->capacity = INITIAL_VECTOR_SIZE;
    container->element_size = element_size;
}

void push_to_vector(Vector* container, void* object) {
    if (container->usage == container->capacity)
        resize_vector(container);

    memcpy((container->data + (container->usage * container->element_size)), object, container->element_size);
    container->usage++;
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

void* at_vector(Vector* container, size_t index) {
    if (index > container->usage) {
        perror("Index Out of Bounds");
        return NULL;
    }

    return container->data + (index * container->element_size);

}


