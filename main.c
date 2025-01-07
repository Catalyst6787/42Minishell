#include "mini.h"

int main(int ac, char **av, char **envp)
{
	char *line;

	(void)ac;
	(void)av;
	line = readline(PROMPT);
	while(ft_strncmp(line, "exit", 4))
	{
		if (*line)
		{
			child_process_for_externs(line, envp);
			add_history(line);
			free(line);
		}
		line = readline(PROMPT);
	}
	rl_clear_history();
	free(line);
	return (0);
}