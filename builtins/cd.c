/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:58:49 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/13 15:15:44 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*get_path_oldpwd(t_env *env)
{
	t_env	*old_pwd;

	old_pwd = get_in_envp(env, "OLDPWD", 6);
	if (old_pwd)
		return (old_pwd->value);
	return (get_in_envp(env, "PWD", 3)->value);
}

void	set_oldpwd(t_env *env, char *pwd)
{
	t_env	*old_pwd;

	old_pwd = get_in_envp(env, "OLDPWD", 6);
	if (!old_pwd)
		return ;
	old_pwd->export = 1;
	free(old_pwd->value);
	old_pwd->value = ft_strdup(pwd);
}

int	ft_cd(char **av, t_env *env)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("minishell: getcwd in cd error"), 1);
	if (!av[1] || (av[1][0] == '-' && av[1][1] == '-'))
		path = get_in_envp(env, "HOME", 4)->value;
	else if (av[1][0] == '-' && !av[1][1])
		path = get_path_oldpwd(env);
	else
		path = av[1];
	if (chdir(path) == -1)
		return (perror("minishell: chdir in cd error"), 1);
	set_oldpwd(env, pwd);
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("minishell: getcwd in cd error"), 1);
	change_value_in_envp(env, "PWD", 3, ft_strdup(pwd));
	free(pwd);
	return (0);
}
