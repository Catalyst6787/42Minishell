#include "mini.h"

void	redirect_builtin(int cmd ,char **av, t_env *env)
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

int	redirect_operator(t_cmd *node, char **envp, t_env *env)
{
	int cmd;

	if (!node || !node->tab)
		return(0);
	cmd = which_cmd(node->tab[0]);
	if (cmd == EXIT)
		return(printf("Goodbye! :)\n"), 0);
	else if (cmd == EXTERNAL)
		child_process_for_externs(node->tab, envp);
	else if (cmd >= PIPE && cmd <= RED_OUTPUT_APPEND)
		printf("Redirection: %s\n", node->tab[0]);
	else if (cmd >= AND)
		printf("BONUS: %s\n", node->tab[0]);
	else
	{
		printf("Builtin:\n"); // TODO put child process_for_builtin here
		redirect_builtin(cmd, node->tab, env);
	}
	return(1);
}
