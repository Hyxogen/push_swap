#include "vector2.h"

void vector_cpy(const t_vec2* src, t_vec2* dest) {
	dest->m_X = src->m_X;
	dest->m_Y = src->m_Y;
}
