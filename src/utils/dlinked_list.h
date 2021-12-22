#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <ft_stdbool.h>
# include <wchar.h>

typedef struct s_dlinked_list {
	void *m_Content;
	struct s_dlinked_list *m_Tail;
	struct s_dlinked_list *m_Head;
} t_dlinked_list;

t_dlinked_list *create_element(void *content);

t_dlinked_list *get_last_element(t_dlinked_list *t_dlinked_list);

t_dlinked_list *find_first(t_dlinked_list *list, ft_bool (*equal)(const void *, const void *), const void *sample);

void add_back(t_dlinked_list **list, t_dlinked_list *element);

void add_before(t_dlinked_list **list, t_dlinked_list *element);

void add_after(t_dlinked_list **list, t_dlinked_list *element);

void remove_elements(t_dlinked_list **list, ft_bool (*equal)(const void *, const void *), const void *sample);

/*TODO Track stack size in struct itself*/
size_t get_size(const t_dlinked_list *list);

void clear_list(t_dlinked_list **list);

void clear_list_elements(t_dlinked_list **list, void (*clear)(void *));

void for_each(t_dlinked_list *list, void (*func)(const void *));

void print_link(const t_dlinked_list *link);

#endif
