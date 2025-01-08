/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:09:47 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/08 14:28:09 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_echo(char **av);

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s", envp[i]);
		ft_printf("\n");
		i++;
	}
}
