#include "mini.h"

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

char	*remove_useless_quotes(char *s)
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

char	*remove_lone_quotes(char *s)
{
	if ((count_chars(s, '\'') % 2) != 0)
		s = rem_char(s, get_last_char(s, '\''));
	if ((count_chars(s, '\"') % 2) != 0)
		s = rem_char(s, get_last_char(s, '\"'));
	return(s);
}

char	*clean_input(char *s)
{
	// expand $
	s = remove_lone_quotes(s); // this makes statements such as echo " quotes:' " impossible but " 'quotes' " work.
	s = remove_useless_quotes(s); 
	// replace wildcard
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
	int		j;
	int		nbr_of_tokens;
	char	**tab;

	i = 0;
	j = 0;
	nbr_of_tokens = count_tokens(s);
	tab = (char **)malloc(sizeof(char *) * (nbr_of_tokens + 1));
	tab[nbr_of_tokens] = NULL;
	while(s[i])
	{
		if (s[i] == ' ')
			i++;
		else if (isquote(s[i]))
		{
			tab[j] = quoted_token_dup(s + i);
			i = end_of_token(s + i) + i + 1;
			j++;
		}
		else
		{
			tab[j] = token_dup(s + i);
			i = end_of_token(s + i) + i;
			j++;
		}
	}
	return(tab);
}

int	count_tokens(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while(s[i])
	{
		if (s[i] == ' ')
			i++;
		else if (isquote(s[i]))
		{
			i = end_of_token(s + i) + i + 1;
			c++;
		}
		else
		{
			i = end_of_token(s + i) + i;
			c++;
		}
	}
	return (c);
}

void	append_node(t_cmd **head, char **tab)
{
	t_cmd *last;
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return(printf("Malloc error in append_node(), exiting"), exit(0)); // Should free_all
	new->tab = tab;
	new->next = NULL;
	if (!head || !(*head))
	{
		*head = new;
		new->id = 0;
		new->prev = NULL;
	}
	else
	{
		last = *head;
		while(last->next)
			last = last->next;
		new->id = last->id + 1;
		last->next = new;
		new->prev = last;
	}
}

char **sub_tab(char **tab, int from, int to)
{
	char **subtab;
	int size;
	int i;

	i = 0;
	if (!tab)
		return(printf("sub_tab was sent bad params, returning NULL"), NULL);
	size = to - from;
	subtab = malloc(sizeof(char *) * (size + 1));
	subtab[size] = NULL;
	while(i < size)
	{
		subtab[i] = tab[from];
		i++;
		from++;
	}
	return(subtab);
}

void	group_tokens(t_cmd **head, char **tab)
{
	int i;
	int group_has_tokens;
	int group_start;

	i = 0;
	group_has_tokens = 0;
	group_start = 0;
	while(tab[i])
	{
		if (is_separator(tab[i]) && group_has_tokens)
		{
			append_node(head, sub_tab(tab, group_start, i));
			append_node(head, sub_tab(tab, i + 0, i + 1));
			i++;
			group_start = i;
			group_has_tokens = 0;
		}
		else
		{
			i++;
			group_has_tokens = 1;
		}
	}
	append_node(head, sub_tab(tab, group_start, i));
}
