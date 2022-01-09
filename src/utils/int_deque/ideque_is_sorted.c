#include "int_deque.h"

/*TODO put function body in private_ function so that it doesn't accsesses the innards of node?*/
ft_bool
	ideque_is_sorted(const t_ideque *deque)
{
	t_inode *node;

	node = ideque_front(deque);
	while (node && node->m_head)
	{
		if (node->m_content > node->m_head->m_content)
			return (FALSE);
		node = node->m_head;
	}
	return (TRUE);
}