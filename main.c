#include "mini.h"

int isquote(char c)
{
	if (c == '\'' || c == '\"')
		return(1);
	else
		return(0);
}

char *remove_useless_quotes(char *s)
{
	int i;

	i = 0;
	while(s[i] && s[i + 1])
	{
		if (isquote(s[i]) && isquote(s[i + 1]))
		{
			// rem two useless quotes
			s = rem_char(s, i); // returns string with s[i] removed (frees og)
			s = rem_char(s, i);
		}
		i++;
	}
}

char *remove_lone_quotes(char *s)
{
	int i;

	i = strchr(s, '\'');
	if (!strchr(*s + i))
		s = rem_char(s, i);
	else
		remove_lone_quotes(*s + i + 1);
}

char **clean_input(char *s)
{
	// expand $
	// remove empty strings and lone quotes
	// split by space except quoted
	// replace wildcard
	// remove quotes
}

int main(int ac, char **av, char **envp)
{
	char *line;

	(void)ac;
	(void)av;
	line = readline(PROMPT);
	while(ft_strncmp(line, "exit", 4))
	{
		if (*line)
		{
			print_tab(clean_input(line));
			//child_process_for_externs(line, envp);
			add_history(line);
			free(line);
		}
		line = readline(PROMPT);
	}
	rl_clear_history();
	free(line);
	return (0);
}
