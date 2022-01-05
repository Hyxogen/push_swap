#include "evaluation.h"

#include <stdlib.h>

void destroy_evaluation(t_evaluation* eval, ft_bool free_self) {
	free(eval->m_Instructions);
	if (free_self)
		free(eval);
}

int cmp_evaluation(const t_evaluation* a, const t_evaluation* b) {
	if (a->m_Count == b->m_Count)
		return (0);
	else if (a->m_Count > b->m_Count)
		return (1);
	else
		return (-1);
}

void init_evaluation(t_evaluation* eval) {
	eval->m_Count = 0;
	eval->m_Instructions = NULL;
	init_vector(&(eval->m_MoveVec));
}
