/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:45:57 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/18 16:12:49 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	count_tokens(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i++;
		else if (isquote(s[i]))
		{
			i = end_of_token(s + i, 0) + i + 1;
			c++;
		}
		else
		{
			i = end_of_token(s + i, 0) + i;
			c++;
		}
	}
	return (c);
}

void	append_node(t_cmd **head, char **tab)
{
	t_cmd	*last;
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (printf("Malloc error in append_node(), exiting"), exit(0));
	new->tab = tab;
	new->next = NULL;
	if (!head || !(*head))
	{
		*head = new;
		new->id = 0;
		new->prev = NULL;
	}
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		new->id = last->id + 1;
		last->next = new;
		new->prev = last;
	}
	new->input = 0;
	new->output = 1;
}

// append node before
void	a_n_b(t_cmd **tail, char **tab, t_cmd **head)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (exit(1));
	new->tab = tab;
	new->id = 0;
	new->input = 0;
	new->output = 1;
	if (*tail)
	{
		new->next = *tail;
		new->prev = (*tail)->prev;
		(*tail)->prev = new;
		if (new->prev)
			new->prev->next = new;
	}
	else
	{
		new->next = NULL;
		new->prev = NULL;
		*tail = new;
		*head = new;
	}
}

char	**sub_tab(char **tab, int from, int to)
{
	char	**subtab;
	int		size;
	int		i;

	i = 0;
	if (!tab)
		return (printf("sub_tab was sent bad params, returning NULL"), NULL);
	size = to - from;
	subtab = malloc(sizeof(char *) * (size + 1));
	subtab[size] = NULL;
	while (i < size)
	{
		subtab[i] = tab[from];
		i++;
		from++;
	}
	return (subtab);
}

int	group_tokens_loop(char **tab, t_cmd **head,
	int *i, int *group_start)
{
	int	group_has_tokens;

	group_has_tokens = 0;
	while (tab[*i])
	{
		if (is_separator(tab[*i]) && group_has_tokens)
		{
			append_node(head, sub_tab(tab, *group_start, *i));
			append_node(head, sub_tab(tab, *i + 0, *i + 1));
			(*i)++;
			*group_start = *i;
			group_has_tokens = 0;
		}
		else
		{
			(*i)++;
			group_has_tokens = 1;
		}
	}
	return (group_has_tokens);
}
