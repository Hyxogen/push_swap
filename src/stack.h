#ifndef STACK_H
# define STACK_H

# include "utils/dlinked_list.h"

/**
 * Tail is towards top of stack from begin
 * Head is towards bottom of stack from begin
 * 
 * Double linked is probably not needed anymore
 * 
 * Top is the newest element pushed on the stack
 * Bottom is the oldest element pushed on the stack
 */

/**
 * m_Head and m_Tail of t_stack_element are undefined
 * 
 */
typedef t_dlinked_list t_stack_element;

typedef struct s_stack {
	t_stack_element	*m_Top;
	t_stack_element	*m_Bottom;
} t_stack;

t_stack *create_stack();

ft_bool push_top_content(t_stack *stack, void *content);
ft_bool push_bottom_content(t_stack *stack, void *content);

ft_bool push_top(t_stack *stack, t_stack_element *element);
ft_bool push_bottom(t_stack *stack, t_stack_element *element);

t_stack_element *pop_top(t_stack *stack);
t_stack_element *pop_bottom(t_stack *stack);

t_stack_element *top(const t_stack *stack);
t_stack_element *bottom(const t_stack *stack);

void rotate(t_stack *stack);
void rrotate(t_stack *stack);

void swap_top(t_stack *stack);

void print_stack(const t_stack *stack);

#endif
