/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_object.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 12:39:19 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/10 09:52:28 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_OBJECT_H
# define PS_OBJECT_H

# include "stack.h"
# include <ft_stdbool.h>

typedef struct s_ps_object {
	t_stack	*m_StackA;
	t_stack *m_StackB;
}	t_ps_object;

t_ps_object *create_ps_object();
void destroy_ps_object(t_ps_object* object, ft_bool free_self);
t_ps_object	*initialize_ps_object(t_ps_object *object);

void fill_psa(t_ps_object *object, int *arr, size_t size);

void print_ps_object(const t_ps_object *object);

void ps_sa(t_ps_object *object);
void ps_sb(t_ps_object *object);
void ps_ss(t_ps_object *object);

void ps_pa(t_ps_object *object);
void ps_pb(t_ps_object *object);

void ps_ra(t_ps_object *object);
void ps_rb(t_ps_object *object);
void ps_rr(t_ps_object *object);

void ps_rra(t_ps_object *object);
void ps_rrb(t_ps_object *object);
void ps_rrr(t_ps_object *object);

t_bool is_sorted(t_ps_object *object);

#endif
