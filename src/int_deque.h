#ifndef DEQUE_H

#include <sys/types.h>
#include <ft_stdbool.h>
#include "push_swap.h"

typedef struct s_inode {
	t_inode* m_tail;
	t_inode* m_head;
	int m_content;
}	t_inode;

typedef struct s_deque {
	t_inode* m_front;
	t_inode* m_back;
	size_t m_size;
}	t_ideque;

void ideque_init(t_ideque* deque, t_inode* front, t_inode* back, size_t size);

void ideque_destroy(t_ideque* deque, ft_bool free_self);

t_ideque* ideque_create_empty();

ft_bool ideque_is_empty(const t_ideque* deque);

size_t ideque_get_size(const t_ideque* deque);

void ideque_push_back(t_ideque* deque, t_inode* node);

void ideque_push_front(t_ideque* deque, t_inode* node);

t_inode* ideque_pop_back(t_ideque* deque);

t_inode* ideque_pop_front(t_ideque* deque);

void ideque_rotate(t_ideque* deque, int val);

void inode_destroy(t_inode* node);

#endif
