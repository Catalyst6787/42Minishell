#include "mini.h"

int main(int ac, char **av, char **envp)
{
	char **tab;
	char *line;
	char *clean_line;
	t_cmd	*groups;
	t_cmd	*tail;
	int		exit;
	t_env	*env;

	groups = NULL;
	tail = NULL;
	exit = 0;
	env = NULL;
	init_envp(&env, envp);
	(void)ac;
	(void)av;

	while(!exit)
	{
		line = readline(PROMPT);
		clean_line = clean_input(line);
		tab = split_tokens(clean_line);
		group_tokens(&groups, tab); // ces 4 lignes peuvent etre combine en un fn d'aide
		tail = groups;
		while(tail)
		{
			printf("\nCMD number: %d\n", tail->id);
			if (!redirect_operator(tail, envp))
				exit = 1;
			tail = tail->next;
		}
		add_history(line);
		free(line);
		line = NULL;
		//free(clean_line);
		clean_line = NULL;
		free_list(&groups);
		groups = NULL;
		free(tab);
		tab = NULL;
	}
	rl_clear_history();
	return (0);
}
