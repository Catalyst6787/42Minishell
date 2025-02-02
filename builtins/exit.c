/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:28:00 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/02 19:29:52 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int fgv_exit_arg(int new)
{
	static int value;
	
	if (new == -1)
		return (value);
	value = new;
	return (value);
}

int	ft_exit(char **av)
{
	if (av[1] && av[2])
		return (printf("minishell: exit: too many arguments\n"), 1);
	if (av[1])
		fgv_exit_arg(ft_atoi(av[1]));
	return (0);
}