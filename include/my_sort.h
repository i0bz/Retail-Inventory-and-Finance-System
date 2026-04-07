#ifndef MY_SORT_H
#define MY_SORT_H

#include "product.h"
#include <stdbool.h>

static bool comparator(Product* x, Product* y) ;
static void swap(Product** x, Product** y);
void my_sort(Product* products[], size_t size);
static void my_qsort(Product* products[], int lower_bound, int upper_bound);
static int lomuto_partition(Product* products[], size_t lower_bound, size_t upper_bound);

static bool comparator(Product* x, Product* y) {
    return x->price < y->price;
}

static void swap(Product** x, Product** y) {
    Product* temp = *x;
    *x = *y;
    *y = temp;
}

void my_sort(Product* products[], size_t size) {
    my_qsort(products, 0, size - 1);
}

static void my_qsort(Product* products[], int lower_bound, int upper_bound) {
    if (lower_bound >= upper_bound) return;

    int pivot = lomuto_partition(products, lower_bound, upper_bound);
    my_qsort(products, lower_bound, pivot - 1);
    my_qsort(products, pivot + 1, upper_bound);

}

static int lomuto_partition(Product* products[], size_t lower_bound, size_t upper_bound) {
    int fast = lower_bound;
    int slow = fast - 1;

    while (fast < upper_bound) {
        if (comparator(products[upper_bound], products[lower_bound])) {
            slow++;
            swap(&products[fast], &products[slow]);
        }
        fast++;
    }

    slow++;
    swap(&products[slow], &products[upper_bound]);
    return slow;
}



#endif