#include "mini.h"

int	redirect_operator(t_cmd *node, char **envp)
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
		print_tab(node->tab);
	}
	return(1);
}
