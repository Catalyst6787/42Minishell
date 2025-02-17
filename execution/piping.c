/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:59:06 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/17 17:59:40 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	create_pipes(t_cmd *head)
{
	t_cmd	*tail;
	int		current_pipe[2];

	tail = head;
	while (tail)
	{
		if (tail->output == 1 && tail->next && tail->next->input == 0)
		{
			pipe(current_pipe);
			tail->output = current_pipe[1];
			tail->next->input = current_pipe[0];
		}
		tail = tail->next;
	}
}

void	close_fd(t_cmd *head)
{
	t_cmd	*tail;

	tail = head;
	while (tail)
	{
		if (tail->input != 0)
			close(tail->input);
		if (tail->output != 1)
			close(tail->output);
		tail = tail->next;
	}
}

void	close_fd_except(t_cmd *head, t_cmd *node)
{
	t_cmd	*tail;

	tail = head;
	while (tail)
	{
		if (tail->input != 0 && tail != node)
			close(tail->input);
		if (tail->output != 1 && tail != node)
			close(tail->output);
		tail = tail->next;
	}
}
