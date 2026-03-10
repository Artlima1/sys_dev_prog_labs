#include "my_lib.hpp"

#include <stdlib.h>

int comp(const void *a, const void *b) {
    return (*(int *)a > *(int *)b);
}

void sort_inplace(int * array, int size){
    std::qsort(array, size, sizeof(int), comp);
}