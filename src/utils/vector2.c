#include "vector2.h"

void cpy_vector(const t_vec2 *src, t_vec2 *dest)
{
	dest->m_X = src->m_X;
	dest->m_Y = src->m_Y;
}

void init_vector(t_vec2 *vec)
{
	vec->m_X = 0;
	vec->m_Y = 0;
}
