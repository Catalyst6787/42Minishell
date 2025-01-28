/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:09:47 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/28 15:00:06 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->export)
		{
			printf("%s=", env->name);
			printf("%s\n", env->value);
		}
		env = env->next;
	}
	return (0);
}
