#ifndef EVALUATION_H
#define EVALUATION_H

#include "../instruction.h"
#include "../../utils/vector2.h"
#include <sys/types.h>

typedef struct s_evaluation {
	size_t m_Count;
	t_vec2 m_MoveVec;
}	t_evaluation;

void init_evaluation(t_evaluation* eval);

void destroy_evaluation(t_evaluation* eval, ft_bool free_self);

int cmp_evaluation(const t_evaluation* a, const t_evaluation* comp);

#endif
