/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:55:35 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/15 17:03:09 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	which_builtin(int cmd, char **av, t_env *env)
{
	int	status;

	if (cmd == ECHO)
		status = ft_echo(av);
	else if (cmd == CD)
		status = ft_cd(av, env);
	else if (cmd == PWD)
		status = ft_pwd();
	else if (cmd == EXPORT)
		status = ft_export(av, env);
	else if (cmd == UNSET)
		status = ft_unset(av, env);
	else if (cmd == ENV)
		status = ft_env(env);
	else if (cmd == RED_INPUT_DEL)
		status = red_input_del(av);
	change_value_in_envp(env, "?", 1, ft_itoa(status));
	return (status);
}

void	exec_parent_process(t_cmd *node, pid_t pid)
{
	if (!node->next)
		fgv_last_pid(pid);
	if (node->input != 0)
		close(node->input);
	if (node->output != 1)
		close(node->output);
}

void	child_process_for_builtins(t_cmd *node, int cmd,
		t_env *env, t_cmd *head)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		reset_signals();
		if (dup2(node->input, STDIN_FILENO) == -1)
			return (printf("errror in dup2"), (void) NULL);
		if (dup2(node->output, STDOUT_FILENO) == -1)
			return (printf("errror in dup2"), (void) NULL);
		close_fd_except(head, node);
		status = which_builtin(cmd, node->tab, env);
		free_envp(&env);
		while (node->prev)
			node = node->prev;
		free_list(&node);
		exit(status);
	}
	else
		exec_parent_process(node, pid);
}

int	redirect_operator(t_cmd *node, char **envp, t_env *env, t_cmd *head)
{
	int	cmd;

	fgv_in_cmd(1);
	if (!node || !node->tab)
		return (0);
	cmd = which_cmd(node->tab[0]);
	if (cmd == EXIT)
		return (ft_exit(node->tab));
	else if (cmd == EXTERNAL)
		child_process_for_externs(node, envp, env, head);
	else
	{
		if (cmd == CD || cmd == EXPORT || cmd == UNSET)
			which_builtin(cmd, node->tab, env);
		else
			child_process_for_builtins(node, cmd, env, head);
	}
	return (1);
}
