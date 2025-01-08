/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:28:50 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/08 15:25:09 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	is_n_option(char *s)
{
	if (!s || !*s)
		return (0);
	if (*s != '-')
		return (0);
	s++;
	while (*s)
	{
		if (*s != 'n')
			return (0);
		s++;
	}
	return (1);
}

void	ft_echo(char **av)
{
	int	i;
	int	opt;

	i = 1;
	opt = 0;
	while (av[i] && is_n_option(av[i]))
	{
		opt = 1;
		i++;
	}
	while (av[i])
	{
		ft_printf("%s", av[i++]);
		if (av[i])
			ft_printf(" ");
	}
	if (!opt)
		ft_printf("\n");
}
