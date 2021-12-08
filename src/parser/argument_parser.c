#include "argument_parser.h"

#include <stdlib.h>

int	ft_atoi(const char* str);

int*	read_arguments(int argc, char **argv)
{
	int	*ret;
	int	*cpy;

	ret = malloc((argc - 1) * sizeof(int));
	if (ret == NULL)
		return (NULL);
	cpy = ret;
	while (argc > 1)
	{
		*cpy  = ft_atoi(argv[argc - 1]);
		cpy++;
		argc--;
	}
	return (ret);
}