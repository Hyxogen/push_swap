/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:56:54 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/13 10:56:54 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <ft_stdio.h>
#include <ft_string.h>
#include <ft_stdbool.h>
#include "../parser/argument_parser.h"
#include "../ps_object.h"
#include "../solver/evaluator.h"
#include "../solver/solver.h"

static ft_bool execute_instruction(const char *inst, t_ps_object *object)
{
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	if (!ft_strcmp(inst, "ra"))
		ps_ra(object);
	else if (!ft_strcmp(inst, "rb"))
		ps_rb(object);	
	else if (!ft_strcmp(inst, "rr"))
		ps_rr(object);
	else if (!ft_strcmp(inst, "sa" ))
		ps_sa(object);
	else if (!ft_strcmp(inst, "sb"))
		ps_sb(object);
	else if (!ft_strcmp(inst, "ss"))
		ps_ss(object);
	else if (!ft_strcmp(inst, "pa"))
		ps_pa(object);
	else if (!ft_strcmp(inst, "pb"))
		ps_pb(object);
	else if (!ft_strcmp(inst, "rra"))
		ps_rra(object);
	else if (!ft_strcmp(inst, "rrb"))
		ps_rrb(object);
	else if (!ft_strcmp(inst, "rrr"))
		ps_rrr(object);
	else
		return (FALSE);
	print_ps_object(object);
	return (TRUE);
}

/*Todo make rename t_read_handle to _read_object and make another typedef for a pointer to t_read_object called t_read_handle*/
static ft_bool execute(t_ps_object *object, t_read_handle *handle)
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
		execute_next_move(object);
		/*printf("Next number that should be processed:%d\n", evaluate_ps(object));*/
		free(ptr);
	}
	free(ptr);
	return (TRUE);
}

int main(int argc, char **argv)
{
	int	*lst;
	t_read_handle	*handle;
	t_ps_object		object;

	if (argc <= 1)
		return (EXIT_SUCCESS);
	handle = start_read(0);
	lst = read_arguments(argc, argv);
	initialize_ps_object(&object);
	fill_psa(&object, lst, argc - 1);
	if (!execute(&object, handle))
		printf("Error\n");
	else if (is_sorted(&object))
		printf("OK\n");
	else
		printf("KO\n");
	free(lst);
	close_read_handle(handle);
	return (EXIT_SUCCESS);
}
