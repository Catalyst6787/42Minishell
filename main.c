#include "mini.h"

int main(int ac, char **av, char **envp)
{
	char *line;
	t_cmd	*groups;
	t_cmd	*tail;
	int		exit;
	t_env	*env;
	int		status;
	pid_t	pid;

	groups = NULL;
	tail = NULL;
	exit = 0;
	env = NULL;
	init_envp(&env, envp);
	handle_signals();
	if (ac != 1)
		printf("no arguments are expected, discarding\n");
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
				// printf("\nCMD number: %d\n", tail->id);
				// printf("INPUT: %d\n", tail->input);
				// printf("OUTPUT: %d\n", tail->output);
				if (!redirect_operator(tail, envp, env))
					exit = 1;
				tail = tail->next;
			}
			pid = 0;
			while (pid != -1)
			{
				pid = wait(&status);
				if (pid != -1 && pid == fgv_last_pid(-1))
				{
					change_value_in_envp(env, "?", 1, ft_itoa(WEXITSTATUS(status) + fgv_sig_nb(-1)));
					fgv_sig_nb(0);
				}
			}
			add_history(line);
			free(line);
			line = NULL;
			print_list(groups); // debug
			close_fd(groups);
			free_list(&groups);
			groups = NULL;
			
			//free_env TODO
		}
	}
	free_envp(&env);
	clear_history();
	return (fgv_exit_arg(-1));
}
