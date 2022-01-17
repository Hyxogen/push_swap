/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argument_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:39:14 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 12:09:41 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "argument_parser.h"

#include "../utils/malloc_utils.h"
#include <ft_stdlib.h>
#include <ft_stdbool.h>
#include <ft_ctype.h>
#include <stdlib.h>

static ft_bool
	ft_catoi(const char *str, int *val)
{
	const char	*cpy;

	*val = 0;
	cpy = str;
	while (ft_isdigit(*str))
	{
		*val = *val * 10 + (*str - '0');
		str++;
	}
	return (*str == '\0' && str != cpy);
}

int
	*read_arguments(int argc, char **argv)
{
	int	*ret;
	int	*cpy;

	ret = ft_safe_malloc((argc - 1) * sizeof(int));
	if (ret == NULL)
		return (NULL);
	cpy = ret;
	while (argc > 1)
	{//TODO if atoi is more than the value of an int, it should stop
		if (!ft_catoi(argv[argc - 1], cpy))
		{
			free(ret);
			return (FALSE);
		}
		cpy++;
		argc--;
	}
	return (ret);
}
