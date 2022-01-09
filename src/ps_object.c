/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ps_object.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/07 12:45:50 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/12/10 12:28:13 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ps_object.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils/malloc_utils.h"

static void _ps_object_px(t_ideque *from, t_ideque *to)
{
	t_inode *pop_node;

	pop_node = ideque_pop_front(from);
	ideque_push_front(to, pop_node);
}

static void ps_object_px(t_ideque *from, t_ideque *to)
{
	if (ideque_is_empty(from))
		return;
	_ps_object_px(from, to);
}

static void _ps_object_sx(t_ideque *deque)
{
	t_inode *first;
	t_inode *second;

	first = ideque_pop_front(deque);
	second = ideque_pop_front(deque);
	ideque_push_front(deque, first);
	ideque_push_front(deque, second);
}

static void ps_object_sx(t_ideque *deque)
{
	if (ideque_get_size(deque) <= 1)
		return;
	_ps_object_sx(deque);
}

void ps_object_init(t_ps_object *object, t_ideque *stack_a, t_ideque *stack_b)
{
	object->m_stack_a = stack_a;
	object->m_stack_b = stack_b;
}

void ps_object_destroy(t_ps_object *object, ft_bool free_self)
{
	ideque_destroy(object->m_stack_a, TRUE);
	ideque_destroy(object->m_stack_b, TRUE);
	if (free_self)
		free(object);
}

t_ps_object *ps_object_create_empty()
{
	t_ps_object *object;

	object = ft_safe_malloc(sizeof(t_ps_object));
	ps_object_init(object, ideque_create_empty(), ideque_create_empty());
	return (object);
}

void ps_object_fill(t_ps_object *object, int *int_arr, size_t arr_len)
{
	while (arr_len--)
	{
		ideque_push_front(object->m_stack_a, inode_create(*int_arr));
		int_arr++;
	}
}

void ps_object_sa(t_ps_object *object)
{
	ps_object_sx(object->m_stack_a);
}

void ps_object_sb(t_ps_object *object)
{
	ps_object_sx(object->m_stack_b);
}

void ps_object_ss(t_ps_object *object)
{
	ps_object_sa(object);
	ps_object_sb(object);
}

void ps_object_pa(t_ps_object *object)
{
	ps_object_px(object->m_stack_b, object->m_stack_a);
}

void ps_object_pb(t_ps_object *object)
{
	ps_object_px(object->m_stack_a, object->m_stack_b);
}

void ps_object_ra(t_ps_object *object)
{
	ideque_rotate(object->m_stack_a, 1);
}

void ps_object_rb(t_ps_object *object)
{
	ideque_rotate(object->m_stack_b, 1);
}

void ps_object_rr(t_ps_object *object)
{
	ps_object_ra(object);
	ps_object_rb(object);
}

void ps_object_rra(t_ps_object *object)
{
	ideque_rotate(object->m_stack_a, -1);
}

void ps_object_rrb(t_ps_object *object)
{
	ideque_rotate(object->m_stack_b, -1);
}

void ps_object_rrr(t_ps_object *object)
{
	ps_object_rra(object);
	ps_object_rrb(object);
}

ft_bool ps_object_is_sorted(const t_ps_object *object)
{
	if (!ideque_is_empty(object->m_stack_b))
		return (FALSE);
	return (ideque_is_sorted(object->m_stack_a));
}

void ps_object_debug_print(const t_ps_object *object)
{
	t_inode *a_node;
	t_inode *b_node;

	a_node = ideque_front(object->m_stack_a);
	b_node = ideque_front(object->m_stack_b);
	printf("%20c|%-2c\n", 'A', 'B');
	printf("----------------------------------------\n");
	while (TRUE)
	{
		if (a_node)
		{
			printf("%20d", a_node->m_content);
			a_node = a_node->m_head;
		} else
			printf("%20.0d", 0);
		if (b_node)
		{
			printf("|%-20d\n", b_node->m_content);
			b_node = b_node->m_head;
		} else
			printf("|%-20.00d\n", 0);
		if (!a_node && !b_node)
			break;
	}
}
