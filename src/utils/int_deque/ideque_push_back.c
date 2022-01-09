#include "int_deque.h"

static void
	_ideque_push_back_empty(t_ideque *deque, t_inode *node)
{
	deque->m_front = node;
	deque->m_back = node;
	deque->m_size = 1;
}

static void
	_ideque_push_back_nempty(t_ideque *deque, t_inode *node)
{
	deque->m_back->m_head = node;
	node->m_tail = deque->m_back;
	deque->m_back = node;
	deque->m_size += 1;
}

void
	ideque_push_back(t_ideque *deque, t_inode *node)
{
	if (ideque_is_empty(deque))
		_ideque_push_back_empty(deque, node);
	else
		_ideque_push_back_nempty(deque, node);
}
