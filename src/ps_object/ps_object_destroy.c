#include "ps_object.h"

#include <stdlib.h>

void
	ps_object_destroy(t_ps_object *object, ft_bool free_self)
{
	ideque_destroy(object->m_stack_a, TRUE);
	ideque_destroy(object->m_stack_b, TRUE);
	if (free_self)
		free(object);
}