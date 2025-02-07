#include "../mini.h"

char	**heredoc(char *del, t_env *env)
{
	int is_single_quoted;
	int first = 1;
	char *tot = ft_strdup("");
	char *line;
	char *to_free;
	char **result;
	char *ndel = NULL;
	if (is_quoted(del, 1, '\'') || is_quoted(del, 1, '\"'))
		is_single_quoted = 1;
	else
		is_single_quoted = 0;
	line = readline(HEREDOC_PROMPT);
	if (is_single_quoted)
	{
		ndel = malloc(sizeof(char) * (ft_strlen(del) - 1));
		ft_memcpy(ndel, del + 1, ft_strlen(del) - 2);
		ndel[ft_strlen(del) - 2] = '\0';
		del = ndel;
	}
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
	if (ndel)
		free(ndel);
	result = malloc(sizeof(char *) * 3);
	result[0] = ft_strdup("<<");
	if (!is_single_quoted)
		result[1] = expand_vars(tot, env, 1);
	else
		result[1] = tot;
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