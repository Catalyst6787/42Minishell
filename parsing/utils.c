/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:46:40 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/17 17:56:00 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	print_list(t_cmd *head)
{
	while (head)
	{
		printf("\nnode nbr: %d\n", head->id);
		printf("node input: %d\n", head->input);
		printf("node output: %d\n", head->output);
		print_tab(head->tab);
		head = head->next;
	}
}

void	free_list(t_cmd **head)
{
	t_cmd	*next;
	t_cmd	*tail;

	if (!head)
		return ;
	tail = *head;
	while (tail)
	{
		free_tab(tail->tab);
		next = tail->next;
		free(tail);
		tail = next;
	}
	head = NULL;
}

void	node_remove(t_cmd *node)
{
	if (node->prev && node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else if (node->prev)
		node->prev->next = NULL;
	else if (node->next)
		node->next->prev = NULL;
	free_tab(node->tab);
	free(node);
}

void	reset_id(t_cmd *node)
{
	if (!node)
		return ;
	node->id = 0;
	node = node->next;
	while (node)
	{
		node->id = node->prev->id + 1;
		node = node->next;
	}
}

// takes a char as input for type of quote, could be anything.
int	is_quoted(char *s, int i, char c)
{
	int	j;

	j = 0;
	i--;
	while (i > -1 && s[i])
	{
		if (s[i] == c)
			j++;
		i--;
	}
	if (j % 2 != 0)
		return (1);
	return (0);
}
