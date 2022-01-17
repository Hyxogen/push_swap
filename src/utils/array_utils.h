/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:23 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:44:21 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_UTILS_H
# define ARRAY_UTILS_H

# include <sys/types.h>
# include <ft_stdbool.h>

int		*iarray_cpy(const int *arr, size_t len);
int		*iarray_cpy_quick_sort(const int *arr, size_t len);
ft_bool	iarray_has_duplicates(const int *arr, size_t len);
#endif
