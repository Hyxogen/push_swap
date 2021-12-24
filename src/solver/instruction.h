#ifndef PUSH_SWAP_INSTRUCTION_H
#define PUSH_SWAP_INSTRUCTION_H

#include "../ps_object.h"

typedef int t_instruction;

typedef void (*t_object_func)(t_ps_object* object);

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

const char* get_instr_name(t_instruction instr);

void execute_instruction(t_instruction instr, t_ps_object* object);

#endif
