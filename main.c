#include "mini.h"

int main(int ac, char **av, char **envp)
{
	char *line;
	t_cmd	*groups;
	t_cmd	*tail;
	int		exit;
	t_env	*env;

	groups = NULL;
	tail = NULL;
	exit = 0;
	env = NULL;
	init_envp(&env, envp);
	handle_signals();
	(void)ac;
	(void)av;

	while(!exit)
	{
		line = readline(PROMPT);
		if (!line)
			exit = 1;
		else if (*line)
		{
			parse_input(line, &groups, env);
			tail = groups;
			create_pipes(groups);
			while(tail)
			{
				//printf("\nCMD number: %d\n", tail->id);
				//printf("INPUT: %d\n", tail->input);
				//printf("OUTPUT: %d\n", tail->output);
				if (!redirect_operator(tail, envp, env))
					exit = 1;
				tail = tail->next;
			}
			add_history(line);
			free(line);
			line = NULL;
			//print_list(groups);
			close_fd(groups);
			free_list(&groups);
			groups = NULL;
			
			//free_env TODO
		}
	}
	free_envp(&env);
	clear_history();
	return (0);
}
