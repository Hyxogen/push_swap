#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

# include <sys/types.h>

void quick_sort(int* arr, size_t len);

int median(int* sorted_arr, size_t len);

int* array_cpy_quick_sort(const int* arr, size_t len);

#endif
