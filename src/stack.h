#ifndef STACK_H
# define STACK_H

# include "utils/dlinked_list.h"
# include <ft_stdbool.h>

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
  * Rather than a stack this is a deque
  */
typedef t_dlinked_list t_stack_element;

typedef struct s_stack {
	t_stack_element* m_Top;
	t_stack_element* m_Bottom;
	size_t m_Size;
} t_stack;

t_stack* create_stack();
void destroy_stack(t_stack* stack, ft_bool free_self);

ft_bool push_top_content(t_stack* stack, void* content);
ft_bool push_bottom_content(t_stack* stack, void* content);

ft_bool push_top(t_stack* stack, t_stack_element* element);
ft_bool push_bottom(t_stack* stack, t_stack_element* element);

t_stack_element* pop_top(t_stack* stack);
t_stack_element* pop_bottom(t_stack* stack);

t_stack_element* stack_top(const t_stack* stack);
t_stack_element* stack_bottom(const t_stack* stack);

t_stack_element* stack_get_next(const t_stack_element* element);
t_stack_element* stack_get_previous(const t_stack_element* element);

void rotate(t_stack* stack);
void rrotate(t_stack* stack);

void swap_top(t_stack* stack);

size_t stack_size(const t_stack* stack);

void print_stack(const t_stack* stack);

#endif
