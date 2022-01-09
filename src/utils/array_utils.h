#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

# include <sys/types.h>

int* iarray_cpy(const int* arr, size_t len);

int* iarray_cpy_quick_sort(const int* arr, size_t len);

#endif
