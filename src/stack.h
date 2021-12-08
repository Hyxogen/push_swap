#ifndef STACK_H
# define STACK_H

# include "utils/dlinked_list.h"

/**
 * Tail is towards top of stack from begin
 * Head is towards bottom of stack from begin
 * 
 */
typedef struct s_stack {
	t_dlinked_list *m_Begin;
} t_stack;

t_stack *create_stack();

t_bool push(t_stack *stack, void *content);

void *pop(t_stack *stack);

void *top(const t_stack *stack);

void rotate(t_stack *stack);

void rrotate(t_stack *stack);

void swap_top(t_stack *stack);

void print_stack(const t_stack *stack);

#endif