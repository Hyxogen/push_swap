#include "../instruction.h"
#include "../../int_deque.h"
#include "sorter.h"
#include <sys/types.h>
#include <limits.h>

size_t
	quick_get_rough_sorted_pos(int val, t_ideque *deque)
{
	(void)val;
	(void)deque;
	return (0);
}

size_t
	_quick_get_full_sorted_pos(int val, const t_inode *current, const t_inode *previous)
{
	size_t	 node_pos;
	size_t	 lowest_pos;
	int		 lowest_val;

	node_pos = 0;
	lowest_pos = 0;
	lowest_val = INT_MAX;
	while (current)
	{
		if (previous->m_content < val && val < current->m_content)
			return (node_pos);
		if (current->m_content < lowest_val)
		{
			lowest_val = current->m_content;
			lowest_pos = node_pos;
		}
		node_pos += 1;
		previous = current;
		current = current->m_head;
	}
	return (lowest_pos);
}

size_t
	quick_get_full_sorted_pos(int val, t_ideque *deque)
{
	if (ideque_get_size(deque) <= 1)
		return (0);
	return (_quick_get_full_sorted_pos(val, ideque_front(deque), ideque_back(deque)));
}

t_instruction
	*_quick_rough_sort_block(t_ps_object *object, int min, int max, size_t *instr_count)
{
	t_sort_info	info;

	info.m_from_deque = object->m_stack_a;
	info.m_to_deque = object->m_stack_b;
	info.m_min = min;
	info.m_max = max;
	info.m_pos_func = quick_get_rough_sorted_pos;
	info.m_put_instr = ips_pb;
	return (sorter_sort(&info, instr_count));
}

t_instruction
	*_quick_full_sort_block(t_ps_object *object, int min, int max, size_t *instr_count)
{
	t_sort_info	info;

	info.m_from_deque = object->m_stack_b;
	info.m_to_deque = object->m_stack_a;
	info.m_min = min;
	info.m_max = max;
	info.m_pos_func = quick_get_full_sorted_pos;
	info.m_put_instr = ips_pb;
	return (sorter_sort(&info, instr_count));
}