#include "../mini.h"

char	*find_path(char *command)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (access(command, X_OK) == 0)
		return (command);
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

void	child_process_for_externs(char *s, char **envp)
{
	char	**av_command;
	char	*path;
	pid_t 	pid;

	av_command = ft_split(s, ' ');
	path = find_path(av_command[0]);
	if (!path)
	{
		ft_printf("minishell: command not found: %s\n", av_command[0]);
		ft_free_split(av_command);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_free_split(av_command);
		free(path);
		return ;
	}
	if (pid == 0)
		execve(path, av_command, envp);
	ft_free_split(av_command);
	free(path);
	waitpid(pid, NULL, 0);
}
