/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:44:58 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/09 13:52:07 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	init_env(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	env->envp = malloc(sizeof(char *) * (i + 1));
	if (!env->envp)
	{
		perror("minishell: malloc envp error");
		return ;
	}
	i = -1;
	while (envp[++i])
		env->envp[i] = ft_strdup(envp[i]);
	env->envp[i] = NULL; 
}