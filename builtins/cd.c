/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:58:49 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/10 14:57:36 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_cd(char **av, t_env *env)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("minishell: getcwd in cd error"));
	if (!av[1] || (av[1][0] == '-' && av[1][1] == '-'))
		path = get_in_envp(env, "HOME", 4)->value;
	else if (av[1][0] == '-' && !av[1][1])
		path = get_in_envp(env, "OLDPWD", 6)->value;
	else
		path = av[1];
	if (chdir(path) == -1)
		return (perror("minishell: chdir in cd error"));
	change_value_in_envp(env, "OlDPWD", 6, pwd);
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("minishell: getcwd in cd error"));
	change_value_in_envp(env, "PWD", 3, pwd);
	free(pwd);
}