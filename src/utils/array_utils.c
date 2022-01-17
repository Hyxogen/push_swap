/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:25 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 15:45:49 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "array_utils.h"
#include "malloc_utils.h"
#include <stdlib.h>
#include <string.h>
#include <ft_string.h>

static void
	int_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void
	iarray_quick_sort(int *arr, size_t len)
{
	size_t		left_index;
	size_t		right_index;
	int			pivot;

	if (len <= 1)
		return ;
	pivot = arr[len / 2];
	left_index = 0;
	right_index = len - 1;
	while (left_index < right_index)
	{
		while (arr[left_index] < pivot)
			left_index++;
		while (arr[right_index] > pivot)
			right_index--;
		if (left_index < right_index)
			int_swap(&arr[left_index], &arr[right_index]);
	}
	iarray_quick_sort(arr, left_index);
	iarray_quick_sort(arr + left_index, len - right_index);
}

int
	*iarray_cpy(const int *arr, size_t len)
{
	int	*cpy;

	cpy = ft_safe_malloc(sizeof(int) * len);
	ft_memcpy(cpy, arr, sizeof(int) * len);
	return (cpy);
}

int
	*iarray_cpy_quick_sort(const int *arr, size_t len)
{
	int	*arr_cpy;

	arr_cpy = iarray_cpy(arr, len);
	ft_memcpy(arr_cpy, arr, sizeof(int) * len);
	iarray_quick_sort(arr_cpy, len);
	return (arr_cpy);
}

t_bool
	iarray_has_duplicates(const int *arr, size_t len)
{
	size_t	check_index;
	size_t	arr_index;

	check_index = 0;
	while (check_index < len)
	{
		arr_index = 0;
		while (arr_index < len)
		{
			if (arr[check_index] == arr[arr_index] && check_index != arr_index)
				return (TRUE);
			arr_index++;
		}
		check_index++;
	}
	return (FALSE);
}
