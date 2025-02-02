#include "../mini.h"

// static char	*get_full_file(int fd)
// {
// 	int first = 1;
// 	char *buf = "";
// 	char *tmp = NULL;
// 	char *full_file = get_next_line(fd);
// 	if (!full_file)
// 		return(NULL);
// 	while(buf || first)
// 	{
// 		tmp = ft_strjoin(full_file, buf);
// 		free(full_file);
// 		if (!first)
// 			free(buf);
// 		first = 0;
// 		buf = NULL;
// 		full_file = tmp;
// 		buf = get_next_line(fd);
// 	}
// 	return(full_file);
// }

// return copy of string until delimiter
// static char	*get_until_string(const char *string, const char *delimiter)
// {
// 	int	i;

// 	i = 0;
// 	if (!string)
// 		return(NULL);
// 	if (!delimiter || !delimiter[0])
// 		return(ft_strdup(string));
// 	while(string[i])
// 	{
// 		if (!ft_strncmp((string + i), delimiter, ft_strlen(delimiter)))
// 		{
// 			if (i == 0)
// 				return (NULL);
// 			return (ft_substr(string, 0, i));
// 		}
// 		i++; 
// 	}
// 	return(ft_strdup(string));
// }

char	**heredoc(char *del, t_env *env)
{
	int first = 1;
	char *tot = ft_strdup("");
	char *line;
	char *to_free;
	char **result;
	line = readline(HEREDOC_PROMPT);
	while(ft_strcmp(line, del))
	{
		if (!first)
		{
			to_free = line;
			line = ft_strjoin("\n", line);
			free(to_free);
		}
		first = 0;
		to_free = tot;
		tot = ft_strjoin(tot, line);
		free(line);
		line = NULL;
		free(to_free);
		to_free = NULL;
		line = readline(HEREDOC_PROMPT);
	}
	free(line);
	result = malloc(sizeof(char *) * 3);
	result[0] = ft_strdup("<<");
	result[1] = expand_vars(tot, env);
	result[2] = NULL;
	return(result);
}


// int	main(int ac, char **av)
// {
// 	if (ac != 2)
// 		return(printf("Usage: ./a.out file\n"), 1);
// 	char **tab = heredoc(av[1]);
// 	print_tab(tab);
// 	free_tab(tab);
// 	return(0);
// }