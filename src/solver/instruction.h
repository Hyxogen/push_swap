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
	ips_stop,
	ips_err
};

const char* get_instr_name(t_instruction instr);

void execute_instruction(t_instruction instr, t_ps_object* object);

void execute_instructions(t_stack* a, t_stack* b, t_instruction* instructions, size_t count);

void join_instructions(t_instruction* a, size_t a_len, t_instruction* b, size_t b_len);

#endif
