/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:36:20 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 11:36:20 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_utils.h"

#include <stdlib.h>

void *ft_safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		exit(EXIT_FAILURE);
		return (NULL);
	}
	return (ret);
}
