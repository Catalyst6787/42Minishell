/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:02:10 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/28 14:12:21 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_unset(char **av, t_env *env)
{
	int		i;

	i = 1;
	while (av[i])
	{
		delete_export_node(&env, av[i], ft_strlen(av[i]));
		i++;
	}
	return (0);
}
