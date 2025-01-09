#include "mini.h"



int main(int ac, char **av, char **envp)
{
	//char *line;

	//if (ac != 2)
	//	return(printf("no args given\n"), 0);
	(void)envp;
	(void)av;
	(void)ac;

	char *res = clean_input(ft_strdup("\"\n\""));
	printf("%s\n\n", res);
	printf("nbr of tokens; %d\n", count_tokens(res));
	split_tokens(res);
	free(res);
	/*
	line = readline(PROMPT);
	while(ft_strncmp(line, "exit", 4))
	{
		if (*line)
		{
			print_tab(clean_input(line));
			//child_process_for_externs(line, envp);
			add_history(line);
			free(line);
		}
		line = readline(PROMPT);
	}
	rl_clear_history();
	free(line);
	*/
	return (0);
}
