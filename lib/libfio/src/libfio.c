#include "libfio.h"
#include <string.h>

static const size_t INITIAL_BUFFERSIZE = 12;


char* getline(FILE* file) {
    char* buffer = malloc(sizeof(char) * INITIAL_BUFFERSIZE);
    if (buffer == NULL) {
        perror("Could not allocate buffer!!!");
        return NULL;
    }

    size_t buffer_size = INITIAL_BUFFERSIZE;


    if (fgets(buffer, buffer_size, file) == NULL) {
        free(buffer);
        return NULL;
    }

    size_t capacity = strlen(buffer);

    if (capacity < buffer_size) return buffer;

    while (buffer[capacity - 1] != '\n') {
        buffer_size *= 2;
        buffer = realloc(buffer, sizeof(char) * buffer_size);

        if (buffer == NULL) {
            perror("Could not allocate buffer!!!");
            free(buffer);
            return NULL;
        }

        if (fgets(buffer, buffer_size - capacity, file) == NULL) break;
        
        capacity = strlen(buffer);
    }
    

    return buffer;
}

