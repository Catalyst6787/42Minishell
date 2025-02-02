#include "../mini.h"

int	which_builtin(int cmd ,char **av, t_env *env)
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

void	child_process_for_builtins(t_cmd *node, int cmd, t_env *env)
{
	pid_t 	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		reset_signals();
		if (node->input != 0)
			if (dup2(node->input, STDIN_FILENO) == -1)
				{
					printf("errror in dup2");
					return ;
				}
		if (node->output != 1)
			if (dup2(node->output, STDOUT_FILENO) == -1)
				{
					printf("errror in dup2");
					return ;
				}
		status = which_builtin(cmd, node->tab, env);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		change_value_in_envp(env, "?", 1, ft_itoa(status));
		if (node->input != 0)
			close(node->input);
		if (node->output != 1)
			close(node->output);
		if (node->next != NULL)
			close(node->output);
 	}
}

int	redirect_operator(t_cmd *node, char **envp, t_env *env)
{
	int cmd;

	in_cmd = 1;
	if (!node || !node->tab)
		return(0);
	cmd = which_cmd(node->tab[0]);
	if (cmd == EXIT)
		return(/*printf("Goodbye! :)\n"), */0);
	else if (cmd == EXTERNAL)
		child_process_for_externs(node, envp, env);
	//else if (cmd >= PIPE && cmd <= RED_OUTPUT_APPEND)
		//printf("Redirection: %s\n", node->tab[0]);
	//else if (cmd >= AND)
		//printf("BONUS: %s\n", node->tab[0]);
	else
	{
		//printf("Builtin:\n"); // TODO put child process_for_builtin here
		if (cmd == CD || cmd == EXPORT || cmd == UNSET)
			which_builtin(cmd, node->tab, env);
		else
			child_process_for_builtins(node, cmd, env);
	}
	in_cmd = 0;
	return (1);
}
