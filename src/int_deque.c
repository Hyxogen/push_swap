#include "int_deque.h"
#include <stdlib.h>
#include "utils/malloc_utils.h"

static void _ideque_push_back_empty(t_ideque* deque, t_inode* node) {
	deque->m_front = node;
	deque->m_back = node;
	deque->m_size = 1;
}

static void _ideque_push_back_nempty(t_ideque* deque, t_inode* node) {
	deque->m_back->m_tail = node;
	deque->m_back = node;
	deque->m_size += 1;
}

static void _ideque_push_front_empty(t_ideque* deque, t_inode* node) {
	deque->m_front = node;
	deque->m_back = node;
	deque->m_size = 1;
}

static void _ideque_push_front_nempty(t_ideque* deque, t_inode* node) {
	deque->m_front->m_tail = node;
	deque->m_front = node;
	deque->m_size += 1;
}

static void _ideque_pop_back_single(t_ideque* deque, t_inode* node) {
	deque->m_front = NULL;
	deque->m_back = NULL;
	deque->m_size = 0;
}

static void _ideque_pop_back_nsingle(t_ideque* deque, t_inode* node) {
	deque->m_back->m_tail->m_head = NULL;
	deque->m_size -= 1;
}

static void _ideque_pop_back(t_ideque* deque) {
	if (ideque_get_size(deque) == 1)
		_ideque_pop_back_single(deque);
	else
		_ideque_pop_back_nsingle(deque);
}

static void _ideque_pop_front_single(t_ideque* deque, t_inode* node) {
	deque->m_front = NULL;
	deque->m_back = NULL;
	deque->m_size = 0;
}

static void _ideque_pop_front_nsingle(t_ideque* deque, t_inode* node) {
	deque->m_front->m_head->m_tail = NULL;
	deque->m_size -= 1;
}

static void _ideque_pop_front(t_ideque* deque) {
	if (ideque_get_size(deque) == 1)
		_ideque_pop_front_single(deque);
	else
		_ideque_pop_front_nsingle(deque);
}

static void _ideque_rotate_forward(t_ideque* deque, unsigned long val) {
	while (val--)
		ideque_push_back(ideque_pop_front(deque));
}

static void _deque_rotate_backward(t_ideque* deque, unsigned long val) {
	while (val--)
		ideque_push_front(ideque_pop_back(deque));
}

static void _ideque_rotate(t_ideque* deque, int val) {
	if (val < 0)
		_deque_rotate_backward(deque, -((long)val));
	else
		_ideque_rotate_forward(deque, val);
}

void ideque_init(t_ideque* deque, t_inode* front, t_inode* back, size_t size) {
	deque->m_front = front;
	deque->m_back = back;
	deque->m_size = size;
}

void ideque_destroy(t_ideque* deque, ft_bool free_self) {
	t_inode* node;
	t_inode* next;

	node = deque->m_front;
	while (node) {
		next = node->m_head;
		inode_destroy(node);
		node = next;
	}
	if (free_self)
		free(deque);
}

t_ideque* ideque_create_empty() {
	t_ideque* deque;

	deque = ft_malloc(sizeof(t_ideque));
	ideque_init(deque, NULL, NULL, 0);
	return (deque);
}

ft_bool ideque_is_empty(const t_ideque* deque) {
	return (ideque_get_size(deque) == 0);
}

size_t ideque_get_size(const t_ideque* deque) {
	return (deque->m_size);
}

void ideque_push_back(t_ideque* deque, t_inode* node) {
	if (ideque_is_empty(deque))
		_ideque_push_back_empty(deque, node);
	else
		_ideque_push_back_nempty(deque, node);
}

void ideque_push_front(t_ideque* deque, t_inode* node) {
	if (ideque_is_empty(deque))
		_ideque_push_front_empty(deque, node);
	else
		_ideque_push_front_nempty(deque, node);
}

t_inode* ideque_pop_back(t_ideque* deque) {
	t_inode* ret;

	if (ideque_is_empty(deque))
		return (NULL);
	ret = deque->m_back;
	_ideque_pop_back(deque);
	return (ret);
}

t_inode* ideque_pop_front(t_ideque* deque) {
	t_inode* ret;

	if (ideque_is_empty(deque))
		return (NULL);
	ret = deque->m_front;
	_ideque_pop_front(deque);
	return (ret);
}

void ideque_rotate(t_ideque* deque, int val) {
	if (ideque_get_size(deque) <= 1)
		return;
	_ideque_rotate(deque, val);
}

void inode_destroy(t_inode* node) {
	free(node);
}
