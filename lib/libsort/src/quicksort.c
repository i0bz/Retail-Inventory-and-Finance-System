#include "m_sort.h"
#include <stdlib.h>
#include <string.h>

static void my_qsort(void* products[], int lower_bound, int upper_bound, size_t element_size);
static int lomuto_partition(void* products[], size_t lower_bound, size_t upper_bound, size_t element_size);


static inline void* get_address(void* begin, size_t index, size_t element_size) {
    return begin + index * element_size;
}


void swap(void** x, void** y, size_t element_size) {
    void* temp = malloc(element_size);
    memcpy(temp, x, element_size);
    memcpy(x, y, element_size);
    memcpy(y, temp, element_size);
    free(temp);
}

void my_sort(void* collection[], size_t size, size_t element_size) {
    my_qsort(collection, 0, size - 1, element_size);
}

static void my_qsort(void* collection[], int lower_bound, int upper_bound, size_t element_size) {
    if (lower_bound >= upper_bound) return;

    int pivot = lomuto_partition(collection, lower_bound, upper_bound, element_size);
    my_qsort(collection, lower_bound, pivot - 1, element_size);
    my_qsort(collection, pivot + 1, upper_bound, element_size);

}

static int lomuto_partition(void* collection[], size_t lower_bound, size_t upper_bound, size_t element_size) {
    int fast = lower_bound;
    int slow = fast - 1;

    while (fast < upper_bound) {
        if (comparator(get_address(collection, fast, element_size), get_address(collection, upper_bound, element_size))) {
            slow++;
            swap(get_address(collection, fast, element_size), get_address(collection, slow, element_size), element_size);
        }
        fast++;
    }

    slow++;
    swap(get_address(collection, slow, element_size), get_address(collection, upper_bound, element_size), element_size);
    return slow;
}

