/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argument_parser.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:39:14 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 15:45:25 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "argument_parser.h"

#include "../utils/malloc_utils.h"
#include <ft_stdlib.h>
#include <ft_stdbool.h>
#include <ft_ctype.h>
#include <stdlib.h>

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
	{/*TODO if atoi is more than the value of an int, it should stop*/
		if (!ft_checked_atoi(argv[argc - 1], cpy))
		{
			free(ret);
			return (FALSE);
		}
		cpy++;
		argc--;
	}
	return (ret);
}
