/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 13:20:10 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/07 15:23:39 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "ps_object.h"

/*
sa
pb
pb
pb
sa
pa
pa
pa
*/
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
	ps_sa(object);
	ps_pb(object);
	ps_pb(object);
	ps_pb(object);
	ps_sa(object);
	ps_pa(object);
	ps_pa(object);
	ps_pa(object);
	printf("\n");
	print_ps_object(object);
	printf("sorted?:%d\n", is_sorted(object));
	return (0);
}