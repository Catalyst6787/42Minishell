#include "mini.h"



int main(int ac, char **av, char **envp)
{
	char **tab;
	t_cmd	*groups;

	//if (ac != 2)
	//	return(printf("no args given\n"), 0);
	(void)envp;
	(void)av;
	(void)ac;
	groups = NULL;

	char *res = clean_input(ft_strdup("this is group one | that is group three > group five is here || double pipe >> double redirection && double ampersand << reverse double redirection"));
	printf("%s\n\n", res);
	printf("nbr of tokens; %d\n", count_tokens(res));
	tab = split_tokens(res);
	print_tab(tab);

	group_tokens(&groups, tab);
	print_list(groups);
	free_list(&groups);

	//free_tab(tab);
	free(tab);
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
