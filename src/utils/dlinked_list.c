#include "dlinked_list.h"
#include <stdlib.h>

t_dlinked_list *create_element(void *content)
{
	t_dlinked_list	*ret;

	ret = malloc(sizeof(t_dlinked_list));
	if (!ret)
		return (NULL);
	ret->m_Content = content;
	ret->m_Tail = 0;
	ret->m_Head = 0;
	return (ret);
}

t_dlinked_list *get_last_element(t_dlinked_list *list)
{
	while (list->m_Head)
		list = list->m_Head;
	return (list);
}

t_dlinked_list *find_first(t_dlinked_list *list, ft_bool (*equal)(const void *, const void *), const void *sample)
{
	while (list && !equal(list->m_Content, sample))
		list = list->m_Head;
	return (list);
}

void add_before(t_dlinked_list **list, t_dlinked_list *element)
{
	if (!*list)
	{
		element->m_Tail = 0;
		element->m_Head = 0;
		*list = element;
		return;
	}
	element->m_Tail = (*list)->m_Tail;
	element->m_Head = *list;

	if ((*list)->m_Tail)
		(*list)->m_Tail->m_Head = element;
	(*list)->m_Tail = element;
}

void add_after(t_dlinked_list **list, t_dlinked_list *element)
{
	if (!*list)
	{
		element->m_Tail = 0;
		element->m_Head = 0;
		*list = element;
		return;
	}
	element->m_Tail = *list;
	element->m_Head = (*list)->m_Head;

	if ((*list)->m_Head)
		(*list)->m_Head->m_Tail = element;
	(*list)->m_Head = element;
}

void add_back(t_dlinked_list **list, t_dlinked_list *element)
{
	t_dlinked_list	*temp;

	temp = *list;
	while (*list)
		*list = (*list)->m_Head;
	element->m_Tail = *list;
	(*list)->m_Head = element;
	if (temp)
		*list = temp;
}

static void remove_element(t_dlinked_list **element)
{
	if ((*element)->m_Tail)
	{
		(*element)->m_Tail->m_Head = (*element)->m_Head;
		if ((*element)->m_Head)
			(*element)->m_Head->m_Tail = (*element)->m_Tail;
	}
	else if ((*element)->m_Head)
	{
		(*element)->m_Head->m_Tail = (*element)->m_Tail;
		*element = (*element)->m_Head;
	}
}

void remove_elements(t_dlinked_list **list, ft_bool (*equal)(const void *, const void *), const void *sample)
{
	t_dlinked_list	*temp;

	temp = *list;
	while (*list)
	{
		if (equal((*list)->m_Content, sample))
			remove_element(list);
		if (!*list)
			break;
		*list = (*list)->m_Head;
	}
}

size_t get_size(const t_dlinked_list *list)
{
	size_t	ret;

	ret = 0;
	while (list)
	{
		ret++;
		list = list->m_Head;
	}
	return (ret);
}

void clear_list(t_dlinked_list **list)
{
	t_dlinked_list	*temp;

	while (*list)
	{
		temp = (*list)->m_Head;
		free(*list);
		*list = temp;
	}
	*list = 0;
}

void clear_list_elements(t_dlinked_list **list, void (*clear)(void *))
{
	t_dlinked_list	*temp;

	while (*list)
	{
		temp = (*list)->m_Head;
		clear((*list)->m_Content);
		free(*list);
		*list = temp;
	}
	*list = 0;
}

void for_each(t_dlinked_list *list, void (*func)(const void *))
{
	while (list)
	{
		func(list->m_Content);
		list = list->m_Head;
	}
}

void print_link(const t_dlinked_list *link)
{
	printf("%p <-T %p H-> %p\n", (void*)link->m_Tail, (void*)link, (void*)link->m_Head);
}
