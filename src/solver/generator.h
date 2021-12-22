#ifndef PUSH_SWAP_GENERATOR_H
#define PUSH_SWAP_GENERATOR_H

# include "distance.h"
# include <sys/types.h>

typedef int t_instruction;

typedef struct s_evaluation {
	size_t				m_Count;
	t_instruction 		*m_Instructions;
}	t_evaluation;

enum instruction {
	ips_empty,
	ips_pa,
	ips_pb,
	ips_ra,
	ips_rb,
	ips_rr,
	ips_sa,
	ips_sb,
	ips_ss,
	ips_rra,
	ips_rrb,
	ips_rrr,
	ips_err
};

/*TODO change to t_instruction*/
t_evaluation generate_instructions(t_distance a, t_distance b);

const char *get_instr_name(t_instruction instr);

#endif
