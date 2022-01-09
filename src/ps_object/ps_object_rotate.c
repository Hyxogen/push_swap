#include "ps_object.h"

void
	ps_object_ra(t_ps_object *object)
{
	ideque_rotate(object->m_stack_a, 1);
}

void
	ps_object_rb(t_ps_object *object)
{
	ideque_rotate(object->m_stack_b, 1);
}

void
	ps_object_rr(t_ps_object *object)
{
	ps_object_ra(object);
	ps_object_rb(object);
}