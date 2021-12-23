#include "array_utils.h"
#include <stdlib.h>
#include <string.h>

static int* get_pivot(int* arr, size_t len) {
	if (len)
		return (&arr[0]);
	return (0);
}

void quick_sort(int* const arr, size_t len) {
	int		pivot;
	int* pivot_addr;
	int* element;
	int* part1;
	int* part2;
	size_t	part1_index;
	size_t	part2_index;
	size_t 	extra;

	if (len <= 1)
		return;
	pivot_addr = get_pivot(arr, len);
	pivot = *pivot_addr;
	part1 = malloc(sizeof(int) * len * 2);
	part2 = &part1[len];
	part1_index = 0;
	part2_index = 0;
	extra = 0;
	while ((part1_index + part2_index + extra) < len) {
		element = &arr[part1_index + part2_index + extra];
		if (element == pivot_addr)
			extra++;
		else if (*element <= pivot)
			part1[part1_index++] = *element;
		else
			part2[part2_index++] = *element;
	}
	quick_sort(part1, part1_index);
	memcpy(arr, part1, sizeof(int) * part1_index);
	arr[part1_index] = pivot;
	quick_sort(part2, part2_index);
	memcpy(arr + part1_index + 1, part2, sizeof(int) * part2_index);
	free(part1);
}

int median(int* sorted_arr, size_t len) {
	if (len & 0x1)
		return ((sorted_arr[len / 2] + sorted_arr[(len / 2) + 1]) / 2);
	return (sorted_arr[len / 2]);
}
