/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:49:53 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/17 16:56:29 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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
