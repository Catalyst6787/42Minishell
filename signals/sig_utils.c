/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:14:08 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/17 16:16:06 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
}

// for heredoc
int	received_signal(int received)
{
	static int	signal;

	if (received == -1)
		signal = 0;
	else if (received == 0)
		return (signal);
	else if (received == SIGINT || received == SIGQUIT)
		signal = received;
	return (0);
}
