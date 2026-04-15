#ifndef M_SORT_H
#define M_SORT_H

#include <stdbool.h>
#include <stddef.h>

bool comparator(void* x, void* y) ;
void swap(void** x, void** y, size_t element_size);

void my_sort(void* collection, size_t size, size_t element_size);



#endif