#ifndef SORTER_H
#define SORTER_H

# include "../instruction.h"
# include "../../int_deque.h"

typedef size_t(*t_pos_func)(int, t_ideque *);

typedef struct s_sort_info
{
	int m_min;
	int m_max;

	t_pos_func m_pos_func;
	t_instruction m_put_instr;
	t_ideque *m_from_deque;
	t_ideque *m_to_deque;

}	t_sort_info;

t_instruction	*sorter_sort(t_sort_info *constraints, size_t *instrs);

#endif
