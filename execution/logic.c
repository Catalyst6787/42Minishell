#include "../mini.h"

void	which_builtin(int cmd ,char **av, t_env *env)
{
	if (cmd == ECHO)
		ft_echo(av);
	else if (cmd == CD)
		ft_cd(av, env);
	else if (cmd == PWD)
		ft_pwd();
	else if (cmd == EXPORT)
		ft_export(av, env);
	else if (cmd == UNSET)
		ft_unset(av, env);
	else if (cmd == ENV)
		ft_env(env);
}

void	child_process_for_builtins(t_cmd *node, int cmd, t_env *env)
{
	pid_t 	pid;

	//node->input = 0; //
	//node->output = 1; // faudra enlever quand lucien a fini
	if (dup2(node->input, STDIN_FILENO) == -1)
		return ;
	if (dup2(node->output, STDOUT_FILENO) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		which_builtin(cmd, node->tab, env); // apres faut vraiment tout free mec
		//free tout et close les fd
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

int	redirect_operator(t_cmd *node, char **envp, t_env *env)
{
	int cmd;

	if (!node || !node->tab)
		return(0);
	cmd = which_cmd(node->tab[0]);
	if (cmd == EXIT)
		return(printf("Goodbye! :)\n"), 0);
	else if (cmd == EXTERNAL)
		child_process_for_externs(node, envp);
	else if (cmd >= PIPE && cmd <= RED_OUTPUT_APPEND)
		printf("Redirection: %s\n", node->tab[0]);
	else if (cmd >= AND)
		printf("BONUS: %s\n", node->tab[0]);
	else
	{
		printf("Builtin:\n"); // TODO put child process_for_builtin here
		child_process_for_builtins(node, cmd, env);
	}
	return(1);
}
