#include "quick_solve.h"
#include <stdlib.h>
#include <ft_string.h>
#include <ft_stdbool.h>
#include <limits.h>

typedef struct s_rotate_inst {
	long	m_Upwards;
	long	m_Downards;
}	t_rotate_inst;

static int ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

static int get_pos(const t_stack *stack, int number)
{
	int	position;
	t_stack_element	*element;

	if (stack == NULL)
	{
		printf("something went wrong!\n");
		return (-1);
	}
	element = stack->m_Top;
	position = 0;
	while (*((int*)element->m_Content) != number)
	{
		position++;
		element = element->m_Head;
		if (element == NULL)
			printf("Something went quite wrong!\n");
	}
	return (position);
}

static t_rotate_inst get_distance(const t_stack *stack, int number)
{
	t_rotate_inst	ret;
	int				distance;

	distance = get_pos(stack, number);
	ret.m_Upwards = distance;
	ret.m_Downards = (stack_size(stack) - distance + 1);
	return (ret);
}

static t_rotate_inst get_closest_pos(const t_stack *stack, int number)
{
	int	closest_num;
	int	distance;
	t_rotate_inst	ret;
	t_stack_element	*element;

	closest_num = 0;
	ret.m_Downards = 0;
	ret.m_Upwards = 0;
	distance = INT_MAX;
	if (stack->m_Top == NULL)
		return (ret);
	element = stack->m_Top;
	while (element)
	{
		if (ft_abs(*((int*)element->m_Content) - number) < distance)
		{
			distance = ft_abs(*((int*)element->m_Content - closest_num));
			closest_num = *((int*)element->m_Content);
		}
		element = element->m_Head;
	}
	printf("Number getting distance for:%d\n", closest_num);
	return (get_distance(stack, closest_num));
}

int evaluate(t_stack *des, t_stack *origin, int number)
{
	t_rotate_inst	origin_inst;
	t_rotate_inst	des_inst;
	t_rotate_inst	total;

	origin_inst = get_distance(origin, number);
	des_inst = get_closest_pos(des, number);

	printf("origin.m_Downards=%ld origin.m_Upwards=%ld\n", origin_inst.m_Downards, origin_inst.m_Upwards);
	printf("des_inst.m_Downards=%ld des_inst.m_Upwards=%ld\n", des_inst.m_Downards, des_inst.m_Upwards);


	total.m_Downards = origin_inst.m_Downards + ft_abs(origin_inst.m_Downards - des_inst.m_Downards);
	total.m_Upwards = origin_inst.m_Upwards + ft_abs(origin_inst.m_Upwards - des_inst.m_Upwards);
	printf("total.m_Downards=%ld total.m_Upwards=%ld\n", total.m_Downards, total.m_Upwards);
	return (0);
}
