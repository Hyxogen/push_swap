#include "int_deque.h"

static void
	_ideque_push_front_empty(t_ideque *deque, t_inode *node)
{
	deque->m_front = node;
	deque->m_back = node;
	deque->m_size = 1;
}

static void
	_ideque_push_front_nempty(t_ideque *deque, t_inode *node)
{
	deque->m_front->m_tail = node;
	node->m_head = deque->m_front;
	deque->m_front = node;
	deque->m_size += 1;
}

void
	ideque_push_front(t_ideque *deque, t_inode *node)
{
	if (ideque_is_empty(deque))
		_ideque_push_front_empty(deque, node);
	else
		_ideque_push_front_nempty(deque, node);
}
