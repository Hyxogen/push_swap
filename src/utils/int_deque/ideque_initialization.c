#include "int_deque.h"

#include "../malloc_utils.h"
#include <stddef.h>

void
	ideque_init(t_ideque *deque, t_inode *front, t_inode *back, size_t size)
{
	deque->m_front = front;
	deque->m_back = back;
	deque->m_size = size;
}

t_ideque
	*ideque_create_empty()
{
	t_ideque *deque;

	deque = ft_safe_malloc(sizeof(t_ideque));
	ideque_init(deque, NULL, NULL, 0);
	return (deque);
}
