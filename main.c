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
		if (line && *line)
		{
			clean_line = clean_input(line);
			tab = split_tokens(clean_line);
			if (group_tokens(&groups, tab)) // ces 4 lignes peuvent etre combine en un fn d'aide
				groups = get_input_output(&groups);
			tail = groups;
			reset_id(groups);
			create_pipes(groups);
			while(tail)
			{
				printf("\nCMD number: %d\n", tail->id);
				printf("INPUT: %d\n", tail->input);
				printf("OUTPUT: %d\n", tail->output);
				if (!redirect_operator(tail, envp, env))
					exit = 1;
				while (wait(NULL) > 0)
					printf("la ça wait\n");
				tail = tail->next;
			}
			printf("\n\nLIST:\n");
			print_list(groups);
			add_history(line);
			free(line);
			line = NULL;
			//free(clean_line);
			clean_line = NULL;
			close_fd(groups);
			free_list(&groups);
			groups = NULL;
			free(tab);
			tab = NULL;
			//free_env() TODO
		}
	}
	free_envp(&env);
	clear_history();
	return (0);
}
