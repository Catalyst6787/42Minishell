#include "../mini.h"

void	ft_free_split(char **tab);

char	*find_path(char *command, char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (access(command, X_OK) == 0)
		return (command);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
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
	path = find_path(av_command[0], envp);
	if (!path)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		execve(path, av_command, envp);
	ft_free_split(av_command);
	waitpid(pid, NULL, 0);
}
