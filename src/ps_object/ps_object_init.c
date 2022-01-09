#include "ps_object.h"

#include "../utils/malloc_utils.h"

void
	ps_object_init(t_ps_object *object, t_ideque *stack_a, t_ideque *stack_b)
{
	object->m_stack_a = stack_a;
	object->m_stack_b = stack_b;
}

t_ps_object
	*ps_object_create_empty()
{
	t_ps_object *object;

	object = ft_safe_malloc(sizeof(t_ps_object));
	ps_object_init(object, ideque_create_empty(), ideque_create_empty());
	return (object);
}
