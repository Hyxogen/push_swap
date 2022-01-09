#include "int_deque.h"

#include <stddef.h>

static void
	_ideque_pop_back_last(t_ideque *deque)
{
	deque->m_front = NULL;
	deque->m_back = NULL;
	deque->m_size = 0;
}

static void
	_ideque_pop_back_nlast(t_ideque *deque)
{
	deque->m_back->m_tail->m_head = NULL;
	deque->m_back = deque->m_back->m_tail;
	deque->m_size -= 1;
}

static void
	_ideque_pop_back(t_ideque *deque)
{
	if (ideque_get_size(deque) == 1)
		_ideque_pop_back_last(deque);
	else
		_ideque_pop_back_nlast(deque);
}

t_inode
	*ideque_pop_back(t_ideque *deque)
{
	t_inode *ret;

	ret = ideque_back(deque);
	_ideque_pop_back(deque);
	ret->m_tail = NULL;
	return (ret);
}
