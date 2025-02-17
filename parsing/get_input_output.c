/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:49:53 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/17 16:47:09 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	handle_pipe(t_cmd **tail)
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

static int	handle_redirection_input(t_cmd **tail, t_cmd **next, t_cmd **last)
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

static int	handle_redirection_output(t_cmd **tail, t_cmd **next)
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

static void	remove_tail_and_next(t_cmd **tail)
{
	node_remove((*tail)->next);
	node_remove(*tail);
	*tail = NULL;
}

static int	handle_heredoc(t_cmd **tail, t_env *env, t_cmd **head, t_cmd **next)
{
	int	sigint_received;

	sigint_received = 0;
	if ((*tail)->next && (*tail)->prev)
	{
		append_node_before(&(*tail)->prev,
			heredoc((*tail)->next->tab[0], env, &sigint_received), head);
		if (sigint_received == 1)
			return (free_list(head), 0);
		*next = (*tail)->next->next;
		(*tail)->prev->input = 0;
	}
	else if ((*tail)->next && (*tail)->next->next)
	{
		append_node_before(tail,
			heredoc((*tail)->next->tab[0], env, &sigint_received), head);
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

static int	handle_red_out_append(t_cmd **tail, t_cmd **next, t_cmd **last)
{
	if ((*tail)->next && (*tail)->prev)
	{
		(*tail)->prev->output = open((*tail)->next->tab[0],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		*next = (*tail)->next->next;
		*last = (*tail)->prev;
		node_remove((*tail)->next);
		node_remove(*tail);
		*tail = NULL;
	}
	else if ((*tail)->next && (*tail)->next->next)
	{
		(*tail)->next->next->output = open((*tail)->next->tab[0],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		*next = (*tail)->next->next;
		*last = (*tail)->next->next;
		node_remove((*tail)->next);
		node_remove(*tail);
		*tail = NULL;
	}
	else
		return (printf("Cannot use a >> without input and output."), 0);
	return (1);
}

static t_cmd	*get_earliest(t_cmd *last)
{
	while (last)
	{
		if (last->prev)
			last = last->prev;
		else
			break ;
	}
	return (last);
}

static void	get_in_out_extra(t_cmd **tail, t_cmd **next, t_cmd **last, int *res)
{
	if (which_cmd((*tail)->tab[0]) == PIPE)
		*res = handle_pipe(tail);
	else if (which_cmd((*tail)->tab[0]) == RED_INPUT)
		*res = handle_redirection_input(tail, next, last);
	else if (which_cmd((*tail)->tab[0]) == RED_OUTPUT)
		*res = handle_redirection_output(tail, next);
	else if (which_cmd((*tail)->tab[0]) == RED_OUTPUT_APPEND)
		*res = handle_red_out_append(tail, next, last);
}

static void	tiny_norme_fn(t_cmd **tail, t_cmd **last, t_cmd **next)
{
	if (*tail)
		*last = *tail;
	*tail = *next;
}

t_cmd	*get_input_output(t_cmd **head, t_env *env)
{
	t_cmd	*tail;
	t_cmd	*next;
	t_cmd	*last;
	int		res;

	res = 1;
	tail = *head;
	next = tail;
	tail->input = 0;
	last = NULL;
	while (tail)
	{
		next = tail->next;
		if (which_cmd(tail->tab[0]) == RED_INPUT_DEL)
		{
			last = tail->prev;
			res = handle_heredoc(&tail, env, head, &next);
		}
		else
			get_in_out_extra(&tail, &next, &last, &res);
		if (!res)
			return (NULL);
		tiny_norme_fn(&tail, &last, &next);
	}
	return (get_earliest(last));
}
