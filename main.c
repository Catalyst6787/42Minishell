#include "mini.h"

int isquote(char c)
{
	if (c == '\'' || c == '\"')
		return(1);
	else
		return(0);
}

// remove char at s[i], frees original s and returns updated string
char	*rem_char(char *s, int t)
{
	int i;
	int j;
	char *nstr;
	nstr = malloc(sizeof(char) * ft_strlen(s));
	nstr[ft_strlen(s) - 1] = '\0';
	i = 0;
	j = 0;
	while(s[j])
	{
		if (j != t)
		{
			nstr[i] = s[j];
			i++;
			j++;
		}
		else
			j++;

	}
	free(s);
	return(nstr);
}

char *remove_useless_quotes(char *s)
{
	int i;

	i = 0;
	while(s[i] && s[i + 1])
	{
		if ((s[i] == '\'' && s[i + 1] == '\'') || (s[i] == '\"' && s[i + 1] == '\"'))
		{
			// rem two useless quotes
			s = rem_char(s, i); // returns string with s[i] removed (frees og)
			s = rem_char(s, i);
			i = 0;
		}
		i++;
	}
	return(s);
}

int get_last_char(char *s, char c)
{
	int i;

	i = ft_strlen(s);
	while(i)
	{
		if (s[i] == c)
			return(i);
		i--;
	}
	return(printf("get_last_char did not found char, exiting"), exit(0), 0);
}

int next_char(char *s, char c)
{
	int i;

	i = 1;
	while(s[i])
	{
		if (s[i] == c)
			return(i);
		i++;
	}
	return(i);
}

int count_chars(char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}	
	return(count);
}

char *remove_lone_quotes(char *s)
{
	if ((count_chars(s, '\'') % 2) != 0)
		s = rem_char(s, get_last_char(s, '\''));
	if ((count_chars(s, '\"') % 2) != 0)
		s = rem_char(s, get_last_char(s, '\"'));
	return(s);
}

char *clean_input(char *s)
{
	// expand $
	s = remove_lone_quotes(s); // this makes statements such as echo " quotes:' " impossible
	s = remove_useless_quotes(s); 
	// split by space except quoted
	// replace wildcard
	// remove quotes
	return(s);
}

int	end_of_token(char *s)
{
	if (isquote(s[0]))
		return(next_char(s, s[0]));
	else
		return(next_char(s, ' '));
}

char	*token_dup(char *s)
{
	int i;
	int t;
	char *dup;

	i = 0;
	t = 0;
	t = end_of_token(s);
	dup = malloc(sizeof(char) * t + 1);
	dup[t] = '\0';
	while(i < t)
	{
		dup[i] = s[i];
		i++;
	}
	return(dup);
}

char	*quoted_token_dup(char *s)
{
	int i;
	int t;

	i = 0;
	t = 0;
	char *dup;
	t = end_of_token(s);
	dup = malloc(sizeof(char) * t);
	dup[t - 1] = '\0';
	while(i < t - 1)
	{
		dup[i] = s[i + 1];
		i++;
	}
	return(dup);
}

char	**split_tokens(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while(s[i])
	{
		if (s[i] == ' ')
			i++;
		else if (isquote(s[i]))
		{
			tmp = quoted_token_dup(s + i);
			printf("%s\n", tmp);
			free(tmp);
			i = end_of_token(s + i) + i + 1;
		}
		else
		{
			tmp = token_dup(s + i);
			printf("%s\n", tmp);
			free(tmp);
			i = end_of_token(s + i) + i;
		}
	}
	return(NULL);
}

int main(int ac, char **av, char **envp)
{
	//char *line;

	//if (ac != 2)
	//	return(printf("no args given\n"), 0);
	(void)envp;
	(void)av;
	(void)ac;

	char *res = clean_input(ft_strdup(" \"quotes: \" "));
	printf("%s\n\n", res);
	split_tokens(res);
	free(res);
	/*
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
	*/
	return (0);
}
