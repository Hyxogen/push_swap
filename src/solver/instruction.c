#include "instruction.h"

static const char* g_InstructionNames[] = {
		"empty",
		"pa",
		"pb",
		"ra",
		"rb",
		"rr",
		"sa",
		"sb",
		"ss",
		"rra",
		"rrb",
		"rrr",
		"err",
		NULL
};

static const t_object_func g_Functions[] = {
		NULL,
		ps_pa,
		ps_pb,
		ps_ra,
		ps_rb,
		ps_rr,
		ps_sa,
		ps_sb,
		ps_ss,
		ps_rra,
		ps_rrb,
		ps_rrr,
		NULL,
		NULL
};

const char* get_instr_name(t_instruction instr) {
	if (instr <= 0 || instr >= ips_err)
		return g_InstructionNames[ips_err];
	return (g_InstructionNames[instr]);
}

void execute_instruction(t_instruction instr, t_ps_object* object) {
	if (instr <= 0 || instr >= ips_err)
		return;
	g_Functions[instr](object);
}