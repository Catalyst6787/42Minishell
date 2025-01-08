/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:28:50 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/08 14:07:31 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_echo(char **av)
{
	int	i;
	int	opt;

	i = 0;
	opt = 0;
	if (ft_strncmp(av[i++], "echo", 4) != 0)
		return ;
	if (av[i] && ft_strncmp(av[i], "-n", 4) == 0)
	{
		opt = 1;
		i++;
	}
	while (av[i])
	{
		ft_printf("%s", av[i++]);
		ft_printf(" ");
	}
	if (!opt)
		ft_printf("\n");
}
