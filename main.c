#include "mini.h"

void	print_tab(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return ;
	while(tab[i])
	{
		printf("tab[%d]: {%s}\n", i, tab[i]);
		i++;
	}
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return ;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int main(int ac, char **av, char **envp)
{
	char **tab;

	//if (ac != 2)
	//	return(printf("no args given\n"), 0);
	(void)envp;
	(void)av;
	(void)ac;

	char *res = clean_input(ft_strdup("test 'quoted' \"double quoted\" \"'triple quoted'\" 0 ' ' "));
	printf("%s\n\n", res);
	printf("nbr of tokens; %d\n", count_tokens(res));
	tab = split_tokens(res);
	print_tab(tab);
	free_tab(tab);
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
