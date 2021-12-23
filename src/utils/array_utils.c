#include "array_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int
	*get_pivot(int *arr, size_t len)
{
	if (len)
		return (&arr[0]);
	return (0);
}

static void print_int_array(int *arr, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		printf("%d,", arr[i]);
	printf("\n");
}

void
	quick_sort(int *arr, size_t len)
{
	int		pivot;
	int		*pivot_addr;
	int		*element;
	int 	*part1;
	int 	*part2;
	size_t	part1_index;
	size_t	part2_index;
	size_t 	extra;

	if (len <= 1)
		return;
	pivot_addr = get_pivot(arr, len);
	pivot = *pivot_addr;
	printf("Pivot:%d\n", *pivot_addr);
	part1 = malloc(sizeof(int) * len * 2);
	part2 = &part1[len];
	part1_index = 0;
	part2_index = 0;
	extra = 0;
	while ((part1_index + part2_index + extra) < len)
	{
		element = &arr[part1_index + part2_index + extra];
		if (element == pivot_addr)
			extra++;
		else if (*element <= pivot)
			part1[part1_index++] = *element;
		else
			part2[part2_index++] = *element;
	}
	quick_sort(part1, part1_index);
	memcpy(arr, part1, part1_index);
	printf("Part1(%zu):", part1_index);
	print_int_array(part1, part1_index);
	printf("Part1(%zu) quick sort result:", part1_index);
	print_int_array(arr, len);
	arr[part1_index] = pivot;
	printf("Pivot placement result result:");
	print_int_array(arr, len);
	quick_sort(part2, part2_index);
	memcpy(arr + part1_index + 1, part2, part2_index);
	printf("Part2(%zu) quick sort result:", part2_index);
	print_int_array(arr, len);
	printf("\n");
	free(part1);
}

int main(void)
{
	int i;
	int arr[] = {5, 8, 7, 6, 9, 4, 3, 2, 1, 0};

	print_int_array(arr, 10);
	quick_sort(arr, 10);
	print_int_array(arr, 10);
	printf("\n");

}
