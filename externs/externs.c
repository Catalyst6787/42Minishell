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

void	child_process_for_externs(t_cmd *node, char **envp)
{
	char	*path;
	pid_t 	pid;

	path = find_path(node->tab[0]);
	node->input = 0; //
	node->output = 1; // faudra enlever quand lucien a fini
	if (dup2(node->input, STDIN_FILENO) == -1)
		return (free(path));
	if (dup2(node->output, STDOUT_FILENO) == -1)
		return (free(path));
	if (!path)
	{
		ft_printf("minishell: command not found: %s\n", node->tab[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return (free(path));
	if (pid == 0)
		execve(path, node->tab, envp);
	free(path);
	waitpid(pid, NULL, 0);
}
