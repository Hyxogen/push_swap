/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   evaluator.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 11:02:42 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/13 16:03:42 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVALUATOR_H
# define EVALUATOR_H

# include "distance.h"
# include "../ps_object.h"
# include <sys/types.h>
# include "generator.h"

t_distance get_distance(const t_stack *stack, int number);

size_t get_position(const t_stack *stack, int number);

void execute_evaluation(t_ps_object *object, const t_evaluation *eval);

t_evaluation	generate_put_pack(t_stack *a, t_stack *b);

t_evaluation	join_evaluations(const t_evaluation *a, const t_evaluation *b);

t_evaluation	evaluate_single_exact(t_stack *origin, t_stack *des, int num, size_t position, size_t size);
t_evaluation	evaluate_single(t_stack *origin, t_stack *des, int number);
t_evaluation	evaluate(t_stack *origin, t_stack *des, int depth);

int	cmp_evaluation(const t_evaluation *a, const t_evaluation *comp);

void print_evaluation(t_evaluation eval);

#endif
