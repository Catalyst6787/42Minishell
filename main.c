#include "mini.h"

static void	setup(char **envp, t_env **env, int *ac, char ***av)
{
	init_envp(env, envp);
	handle_signals();
	if (*ac != 1)
		printf("no arguments are expected, discarding\n");
	(void)ac;
	(void)av;
}

static void	wait_for_pids(t_env *env)
{
	int		status;
	pid_t	pid;

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
}

static t_cmd*	init_list(char *line, t_cmd **groups, t_env *env)
{
	parse_input(line, groups, env);
	handle_signals();
	create_pipes(*groups);
	return(*groups);
}

// static void	handle_cmds(char **line, char **envp, t_env **env, t_cmd **groups)
// {

// }

int main(int ac, char **av, char **envp)
{
	char	*line;
	t_cmd	*groups;
	t_cmd	*tail;
	int		exit;
	t_env	*env;

	groups = NULL;
	tail = NULL;
	exit = 0;
	env = NULL;
	setup(envp, &env, &ac, &av);
	while(!exit)
	{
		line = readline(PROMPT);
		if (!line)
			exit = 1;
		else if (*line)
		{
			tail = init_list(line, &groups, env);
			while(tail)
			{
				if (!redirect_operator(tail, envp, env, groups))
					exit = 1;
				tail = tail->next;
			}
			wait_for_pids(env);
			add_history(line);
			free(line);
			line = NULL;
			close_fd(groups);
			free_list(&groups);
			groups = NULL;
		}
	}
	free_envp(&env);
	clear_history();
	return (fgv_exit_arg(-1));
}
