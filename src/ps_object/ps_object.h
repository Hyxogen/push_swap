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

# include "../utils/int_deque/int_deque.h"
# include <ft_stdbool.h>
# include <sys/types.h>

typedef struct s_ps_object
{
	t_ideque *m_stack_a;
	t_ideque *m_stack_b;
}	t_ps_object;

void	ps_object_init(t_ps_object *object, t_ideque *stack_a, t_ideque *stack_b);
void	ps_object_destroy(t_ps_object *object, ft_bool free_self);

/*MALLOC SAFE*/
t_ps_object	*ps_object_create_empty();

void		ps_object_fill(t_ps_object *object, int *int_arr, size_t arr_len);

void		ps_object_sa(t_ps_object *object);
void		ps_object_sb(t_ps_object *object);
void		ps_object_ss(t_ps_object *object);

void		ps_object_pa(t_ps_object *object);
void		ps_object_pb(t_ps_object *object);

void		ps_object_ra(t_ps_object *object);
void		ps_object_rb(t_ps_object *object);
void		ps_object_rr(t_ps_object *object);

void		ps_object_rra(t_ps_object *object);
void		ps_object_rrb(t_ps_object *object);
void		ps_object_rrr(t_ps_object *object);

ft_bool		ps_object_is_sorted(const t_ps_object *object);

#endif
