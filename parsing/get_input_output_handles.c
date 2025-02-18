/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output_handles.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:54:42 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/18 16:14:08 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	handle_pipe(t_cmd **tail)
{
	if ((*tail)->prev && (*tail)->next)
	{
		(*tail)->prev->output = 1;
		(*tail)->next->input = 0;
		node_remove(*tail);
		*tail = NULL;
	}
	else
		return (0);
	return (1);
}

int	handle_redirection_input(t_cmd **tail, t_cmd **next, t_cmd **last)
{
	if ((*tail)->next && (*tail)->prev)
	{
		(*tail)->prev->input = open((*tail)->next->tab[0], O_RDONLY);
		if (((*tail)->prev->input) == -1)
			return ((*tail)->prev->input = 0, 0);
		(*next) = (*tail)->next->next;
		*last = (*tail)->prev;
	}
	else if ((*tail)->next && (*tail)->next->next)
	{
		(*tail)->next->next->input = open((*tail)->next->tab[0], O_RDONLY);
		if (((*tail)->next->next->input) == -1)
			return (printf("file '%s' doesnt exist\n",
					(*tail)->next->tab[0]), (*tail)->next->next->input = 0, 0);
		*next = (*tail)->next->next;
		*last = (*tail)->next->next;
	}
	else
		return (printf("Error, < needs input and output."), 0);
	node_remove((*tail)->next);
	node_remove(*tail);
	*tail = NULL;
	return (1);
}

static void	remove_tail_and_next(t_cmd **tail)
{
	node_remove((*tail)->next);
	node_remove(*tail);
	*tail = NULL;
}

int	handle_heredoc(t_cmd **tail, t_env *env, t_cmd **head, t_cmd **next)
{
	int	sigint_received;

	sigint_received = 0;
	if ((*tail)->next && (*tail)->prev)
	{
		a_n_b(&(*tail)->prev, heredoc(ft_strdup((*tail)->next->tab[0]),
				env, &sigint_received), head);
		if (sigint_received == 1)
			return (free_list(head), 0);
		*next = (*tail)->next->next;
		(*tail)->prev->input = 0;
	}
	else if ((*tail)->next && (*tail)->next->next)
	{
		a_n_b(tail, heredoc(ft_strdup((*tail)->next->tab[0]),
				env, &sigint_received), head);
		if (sigint_received == 1)
			return (free_list(head), 0);
		*next = (*tail)->next->next;
		(*tail)->next->next->input = 0;
	}
	else
		return (printf("Cannot use << without input and output.\n"), 0);
	remove_tail_and_next(tail);
	return (1);
}

int	handle_redirection_output(t_cmd **tail, t_cmd **next)
{
	if ((*tail)->next && (*tail)->prev)
	{
		(*tail)->prev->output = open((*tail)->next->tab[0],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		*next = (*tail)->next->next;
		node_remove((*tail)->next);
		node_remove(*tail);
		*tail = NULL;
	}
	else if ((*tail)->next && (*tail)->next->next)
	{
		(*tail)->next->next->output = open((*tail)->next->tab[0],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		*next = (*tail)->next->next;
		node_remove((*tail)->next);
		node_remove(*tail);
		*tail = NULL;
	}
	else
		return (printf("Cannot use > without input and output.\n"), 0);
	return (1);
}
