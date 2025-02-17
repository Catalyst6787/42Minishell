#include "mini.h"

int	get_exit_status(t_env *env)
{
	t_env	*exit_status;

	if (fgv_exit_arg(-1))
		return (fgv_exit_arg(-1));
	exit_status = get_in_envp(env, "?", 1);
	return (atoi(exit_status->value));
}

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
			handle_signals();
			tail = groups;
			create_pipes(groups);
			while(tail)
			{
				// printf("\nCMD number: %d\n", tail->id);
				// printf("INPUT: %d\n", tail->input);
				// printf("OUTPUT: %d\n", tail->output);
				if (!redirect_operator(tail, envp, env, groups))
					exit = 1;
				tail = tail->next;
			}
			pid = 0;
			while (pid != -1)
			{
				pid = wait(&status);
				if (pid != -1 && pid == fgv_last_pid(-1))
				{
					if (fgv_sig_nb(-1))
						change_value_in_envp(env, "?", 1, ft_itoa(fgv_sig_nb(-1)));
					else
						change_value_in_envp(env, "?", 1, ft_itoa(WEXITSTATUS(status)));
					fgv_sig_nb(0);
				}
			}
			fgv_in_cmd(0);
			add_history(line);
			free(line);
			line = NULL;
			//print_list(groups); // debug
			close_fd(groups);
			free_list(&groups);
			groups = NULL;
			
			//free_env TODO
		}
	}
	status = get_exit_status(env);
	free_envp(&env);
	clear_history();
	return (status);
}
