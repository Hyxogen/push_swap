#include <stdlib.h>
#include <stdio.h>
#include <ft_stdio.h>
#include "../parser/argument_parser.h"

int main(int argc, char **argv)
{
	int	*lst;
	int	i;
	char *ptr;
	t_read_handle	*handle;

	if (argc <= 1)
		return (EXIT_SUCCESS);
	handle = start_read(0);
	lst = read_arguments(argc, argv);
	while (ft_getdelim(&ptr, handle, '\n'))
		printf("%s\n", ptr);
	for (i = 0; i < (argc - 1); i++)
		printf("%d\n", lst[i]);
	free(lst);
	close_read_handle(handle);
	return (EXIT_SUCCESS);
}
