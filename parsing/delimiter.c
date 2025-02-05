#include "../mini.h"

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