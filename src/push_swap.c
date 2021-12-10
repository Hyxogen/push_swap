/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 13:20:10 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/10 13:06:32 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "ps_object.h"
#include "solver/slow_solver.h"
#include "parser/argument_parser.h"
#include <stdlib.h>

/*
sa
pb
pb
pb
sa
pa
pa
pa
int
	main(void)
{
	t_ps_object *object;
	
	object = create_ps_object();
	// int arr[6] = {
	// 	2, 1, 3, 6, 5, 8
	// };

	int arr[6] = {
		8, 5, 6, 3, 1, 2
	};

	fill_psa(object, &arr[0], 6);
	print_ps_object(object);
	printf("\n");
	print_ps_object(object);
	printf("sorted?:%d\n", is_sorted(object));
	return (0);
}
*/

int
	main(int argc, char **argv)
{
	int	*lst;
	t_ps_object		object;

	if (argc <= 1)
		return (EXIT_SUCCESS);
	lst = read_arguments(argc, argv);
	initialize_ps_object(&object);
	fill_psa(&object, lst, argc - 1);
	slow_solve(&object);
	free(lst);
	return (EXIT_SUCCESS);
}
