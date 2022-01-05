#include "instruction.h"

#include <ft_string.h>
#include <ft_stdlib.h>
#include <stdio.h>
#include <stdlib.h>

static const char* g_DefaultNames[] = {
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
		"",
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

static const char* g_ErrorInst = "err";

const char* get_instr_name(t_instruction instr) {
	return (get_instr_name_l(instr, g_DefaultNames, ips_err));
}

const char* get_instr_name_l(t_instruction instr, const char** locale, int locale_size) {
	if (instr <= 0 || instr >= locale_size)
		return (g_ErrorInst);
	return (locale[instr]);
}

void execute_instruction(t_instruction instr, t_ps_object* object) {
	if (instr <= 0 || instr >= ips_err)
		return;
	g_Functions[instr](object);
}

void execute_instructions(t_stack* a, t_stack* b, t_instruction* instructions, size_t count) {
	t_ps_object object;
	
	init_ps_object_stacks(&object, a, b);
	while (count) {
		execute_instruction(*instructions, &object);
		instructions++;
		count--;
	}
}

void print_instructions(t_instruction* instructions, size_t count) {
	print_instructions_l(instructions, count, g_DefaultNames, ips_err);
}

void print_instructions_l(t_instruction* instructions, size_t count, const char** locale, int locale_size) {
	while (count) {
		printf("%s\n", get_instr_name_l(*instructions, locale, locale_size));
		count--;
		instructions++;
	}
}

/** TODO check if this works */
void join_instructions(t_instruction** a, size_t a_len, t_instruction* b, size_t b_len) {
	t_instruction* ptr;

	ptr = ft_realloc(*a, a_len * sizeof(t_instruction), (a_len + b_len) * sizeof(t_instruction)); /*TODO make this ft_realloc use the malloc wa*/
	if (ptr == NULL)
		return; /*TODO This should exit the program*/
	ft_memcpy(ptr + a_len, b, b_len * sizeof(t_instruction));
	*a = ptr;
}

void destroy_instruction(t_instruction* instr, ft_bool free_self) {
	if (free_self)
		free(instr);
}

t_instruction translate_instruction(t_instruction instr, const t_instruction* translation) {
	if (instr < 0 || instr > ips_err)
		return (ips_err);
	return (translation[instr]);
}

void translate_instructions(t_instruction* instructions, size_t count, const t_instruction* translation) {
	while (count) {
		*instructions = translate_instruction(*instructions, translation);
		count--;
		instructions++;
	}
}
