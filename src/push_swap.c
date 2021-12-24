/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 13:20:10 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/16 09:28:38 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "ps_object.h"
#include "parser/argument_parser.h"
#include "solver/evaluator.h"
#include <stdlib.h>

static ft_bool execute_self_solve(t_ps_object* object) {
	t_evaluation eval;

	while (object->m_StackA->m_Top) {
		eval = evaluate(object->m_StackA, object->m_StackB, 0);
		if (eval.m_Count == 0)
			break;
		execute_evaluation(object, &eval);
		print_evaluation(eval);
		destroy_evaluation(&eval, FALSE);
	}
	eval = generate_put_pack(object->m_StackA, object->m_StackB);
	execute_evaluation(object, &eval);
	print_evaluation(eval);
	destroy_evaluation(&eval, FALSE);
	return (is_sorted(object));
}

int
main(int argc, char** argv) {
	int* lst;
	t_ps_object		object;

	if (argc <= 1)
		return (EXIT_SUCCESS);
	lst = read_arguments(argc, argv);
	initialize_ps_object(&object);
	fill_psa(&object, lst, argc - 1);
	execute_self_solve(&object);
	free(lst);
	destroy_ps_object(&object, FALSE);
	return (EXIT_SUCCESS);
}
