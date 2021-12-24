#ifndef ARGUMENT_PARSER_H
# define ARGUMENT_PARSER_H

/**
 * @brief Puts the arguments into an array that can then correctly be pushed onto a stack
 * Behaviour is undefined if you pass only the program name argument
 *
 * @param argc argument count passed to main at program start
 * @param argv an array of string with the arguments
 * @return NULL if internal malloc went wrong
 */
int* read_arguments(int argc, char** argv);

#endif
