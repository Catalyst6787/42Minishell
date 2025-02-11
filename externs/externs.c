/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:09:19 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/11 13:11:47 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*find_path(char *command, t_env *env)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;
	t_env	*PATH;

	i = 0;
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	PATH = get_in_envp(env, "PATH", 4);
	if (!PATH)
		return (NULL);
	paths = ft_split(PATH->value, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

void	child_process_for_externs(t_cmd *node, char **envp, t_env *env)
{
	char	*path;
	pid_t	pid;

	path = find_path(node->tab[0], env);
	if (!path)
	{
		ft_printf("minishell: command not found: %s\n", node->tab[0]);
		change_value_in_envp(fgv_env(NULL), "?", 1, ft_strdup("127"));
		return ;
	}
	pid = fork();
	if (pid == -1)
		return (free(path));
	if (pid == 0)
	{
		reset_signals();
		if (node->input != 0)
			if (dup2(node->input, STDIN_FILENO) == -1)
				return (printf("errror in dup2"), free(path));
		if (node->output != 1)
			if (dup2(node->output, STDOUT_FILENO) == -1)
				return (printf("errror in dup2"), free(path));
		execve(path, node->tab, envp);
		exit(0);
	}
	else
	{
		if (!node->next)
			fgv_last_pid(pid);
		if (node->input != 0)
			close(node->input);
		if (node->output != 1)
			close(node->output);
	}
	free(path);
}
