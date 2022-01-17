/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:56:54 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 15:45:49 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../locale.h"
#include "../parser/argument_parser.h"
#include "../ps_object/ps_object.h"
#include "../utils/array_utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ft_stdio.h>
#include <ft_string.h>
#include <ft_stdbool.h>

static t_bool
	execute_instruction(const char *inst, t_ps_object *object)
{
	if (!ft_strcmp(inst, "ra"))
		ps_object_ra(object);
	else if (!ft_strcmp(inst, "rb"))
		ps_object_rb(object);
	else if (!ft_strcmp(inst, "rr"))
		ps_object_rr(object);
	else if (!ft_strcmp(inst, "sa"))
		ps_object_sa(object);
	else if (!ft_strcmp(inst, "sb"))
		ps_object_sb(object);
	else if (!ft_strcmp(inst, "ss"))
		ps_object_ss(object);
	else if (!ft_strcmp(inst, "pa"))
		ps_object_pa(object);
	else if (!ft_strcmp(inst, "pb"))
		ps_object_pb(object);
	else if (!ft_strcmp(inst, "rra"))
		ps_object_rra(object);
	else if (!ft_strcmp(inst, "rrb"))
		ps_object_rrb(object);
	else if (!ft_strcmp(inst, "rrr"))
		ps_object_rrr(object);
	else
		return (FALSE);
	return (TRUE);
}

static t_bool
	execute(t_ps_object *object, t_read_handle *handle)
{
	char	*ptr;

	ptr = NULL;
	while (ft_getdelim(&ptr, handle, '\n'))
	{
		if (!execute_instruction(ptr, object))
		{
			free(ptr);
			return (FALSE);
		}
		free(ptr);
	}
	free(ptr);
	return (TRUE);
}

int
	run(int *lst, size_t len, t_read_handle *handle)
{
	t_ps_object	*object;
	int			ret_code;

	object = ps_object_create_empty();
	ps_object_fill(object, lst, len);
	ret_code = EXIT_SUCCESS;
	if (!execute(object, handle))
	{
		ft_putendl_fd(2, PS_ERROR_MESSAGE);
		ret_code = EXIT_FAILURE;
	}
	else if (ps_object_is_sorted(object))
		ft_putendl_fd(1, PS_OK_MESSAGE);
	else
		ft_putendl_fd(1, PS_KO_MESSAGE);
	ps_object_destroy(object, TRUE);
	return (ret_code);
}

int
	main(int argc, char **argv)
{
	t_read_handle	*handle;
	int				*lst;
	int				ret_code;

	if (argc <= 1)
		return (EXIT_SUCCESS);
	lst = read_arguments(argc, argv);
	handle = start_read(0);
	if (lst == NULL || iarray_has_duplicates(lst, argc - 1)
		|| handle == NULL)
	{
		ft_putendl_fd(2, PS_ERROR_MESSAGE);
		free(lst);
		close_read_handle(handle);
		return (EXIT_FAILURE);
	}
	ret_code = run(lst, argc - 1, handle);
	free(lst);
	close_read_handle(handle);
	return (ret_code);
}
