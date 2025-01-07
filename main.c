#include "mini.h"

int main(int ac, char **av, char **envp)
{
	char *line;

	(void)ac;
	(void)av;
	line = readline("dis moi tout > ");
	while(ft_strncmp(line, "exit", 4))
	{
		child_process_for_externs(line, envp);
		add_history(line);
		free(line);
		line = readline("dis moi tout > ");
	}
	rl_clear_history();
	free(line);
	return (0);
}