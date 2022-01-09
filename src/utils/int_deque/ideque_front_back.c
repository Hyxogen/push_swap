#include "int_deque.h"

t_inode
	*ideque_back(const t_ideque *deque)
{
	return (deque->m_back);
}

t_inode
	*ideque_front(const t_ideque *deque)
{
	return (deque->m_front);
}
