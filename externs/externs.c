/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:09:19 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/15 16:54:44 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*find_path(char *command, t_env *env)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;
	t_env	*path_node;

	i = 0;
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	path_node = get_in_envp(env, "PATH", 4);
	if (!path_node)
		return (NULL);
	paths = ft_split(path_node->value, ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (ft_free_split(paths), path);
		free(path);
	}
	ft_free_split(paths);
	return (NULL);
}

void	exec_child_process(t_cmd *node, char **envp,
	char *path, t_cmd *head)
{
	reset_signals();
	if (dup2(node->input, STDIN_FILENO) == -1)
		return (printf("errror in dup2"), free(path));
	if (dup2(node->output, STDOUT_FILENO) == -1)
		return (printf("errror in dup2"), free(path));
	close_fd_except(head, node);
	execve(path, node->tab, envp);
	exit(0);
}

void	child_process_for_externs(t_cmd *node, char **envp,
		t_env *env, t_cmd *head)
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
		exec_child_process(node, envp, path, head);
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
