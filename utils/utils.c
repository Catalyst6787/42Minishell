/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:15:30 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/18 15:19:20 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	get_exit_status(t_env *env)
{
	t_env	*exit_status;

	if (fgv_exit_arg(-1))
		return (fgv_exit_arg(-1));
	exit_status = get_in_envp(env, "?", 1);
	return (atoi(exit_status->value));
}
