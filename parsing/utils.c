#include "mini.h"

int	which_cmd(char *cmd)
{
	if (!strcmp(cmd, "echo"))
		return(ECHO);
	else if (!strcmp(cmd, "cd"))
		return(CD);
	else if (!strcmp(cmd, "pwd"))
		return(PWD);
	else if (!strcmp(cmd, "export"))
		return(EXPORT);
	else if (!strcmp(cmd, "unset"))
		return(UNSET);
	else if (!strcmp(cmd, "env"))
		return(ENV);
	else if (!strcmp(cmd, "exit"))
		return(EXIT);
	else
		return(EXTERNAL);
	
}

int	is_special(char c)
{
	if (c == '<' || c == '>')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '$')
		return (1);
	else if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int	isquote(char c)
{
	if (c == '\'' || c == '\"')
		return(1);
	else
		return(0);
}

int	get_last_char(char *s, char c)
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

int	next_char(char *s, char c)
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

int	count_chars(char *s, char c)
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
