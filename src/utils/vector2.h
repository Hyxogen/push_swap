#ifndef VECTOR2_H
#define VECTOR2_H

typedef struct s_vec2 {
	long m_X;
	long m_Y;
}	t_vec2;

void vector_cpy(const t_vec2* src, t_vec2* dest);

void init_vector(t_vec2* vec);

#endif
