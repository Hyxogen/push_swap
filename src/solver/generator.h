#ifndef PUSH_SWAP_GENERATOR_H
#define PUSH_SWAP_GENERATOR_H

# include "distance.h"
# include <sys/types.h>
# include "instruction.h"
# include <ft_stdbool.h>

typedef struct s_evaluation {
	size_t				m_Count;
	t_instruction 		*m_Instructions;
}	t_evaluation;

/*TODO change to t_instruction*/
t_evaluation generate_instructions(t_distance a, t_distance b);
void destroy_evaluation(t_evaluation* eval, ft_bool free_self);


#endif
