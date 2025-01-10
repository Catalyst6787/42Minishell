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
	else if (!strcmp(cmd, "|"))
		return(PIPE);
	else if (!strcmp(cmd, "<"))
		return(RED_INPUT);
	else if (!strcmp(cmd, ">"))
		return(RED_OUTPUT);
	else if (!strcmp(cmd, "<<"))
		return(RED_INPUT_DEL);
	else if (!strcmp(cmd, ">>"))
		return(RED_OUTPUT_APPEND);
	else if (!strcmp(cmd, "&&"))
		return(AND);
	else if (!strcmp(cmd, "||"))
		return(OR);
	else if (!strcmp(cmd, "("))
		return(PAR_OPEN);
	else if (!strcmp(cmd, ")"))
		return(PAR_CLOSE);
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

int is_separator(char *s)
{
	if ((ft_strlen(s) == 1 || (ft_strlen(s) == 2 && s[0] == s[1]))
	&& (s[0] == '|' || s[0] == '>' || s[0] == '<'))
		return (1);
	else if (ft_strlen(s) == 2 && s[0] == s[1] && s[0] == '&')
		return(1);
	else
		return(0);
}

int next_separator(char **tab, int i)
{
	while(tab[i])
	{
		if (is_separator(tab[i]))
			return(i);
		i++;
	}
	return(0);
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

void	print_tab(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return ;
	while(tab[i])
	{
		printf("tab[%d]: {%s}\n", i, tab[i]);
		i++;
	}
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return ;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	print_list(t_cmd *head)
{
	while(head)
	{
		printf("\nnode nbr: %d\n", head->id);
		print_tab(head->tab);
		head = head->next;
	}
}


void	free_list(t_cmd **head)
{
	t_cmd *next;
	t_cmd *tail;

	if (!head)
		return ;
	tail = *head;
	while(tail)
	{
		free_tab(tail->tab);
		next = tail->next;
		free(tail);
		tail = next;
	}
	head = NULL;
}
