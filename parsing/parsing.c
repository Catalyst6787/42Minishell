#include "../mini.h"

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

char *remove_lone_quote_specify(char *s, char c)
{
	s = rem_char(s, get_last_char(s, c));
	return(s);
}


char	*clean_input(char *s)
{
	int is_changed = 1;
	while(is_changed)
		s = clean_quotes(s, &is_changed);
	s = clean_useless_quotes(s);
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
	new->input = 0;
	new->output = 1;
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

int	group_tokens(t_cmd **head, char **tab)
{
	int i;
	int group_has_tokens;
	int group_start;

	i = 0;
	group_has_tokens = 0;
	group_start = 0;
	if (!tab || !tab[0])
		return(printf("Error: group_tokens encountered empty cmd\n"), 0);
	if (tab[0][i] == '<')
	{
		if (!tab[0] || !tab[1] || !tab[2])
			return(printf("Error: '<'/'<<' Must be followed by input file and command\n"), 0);
		append_node(head, sub_tab(tab, 0, 1));
		append_node(head, sub_tab(tab, 1, 2));
		i += 2;
		group_start = i;
	}
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
	if (group_has_tokens)
		append_node(head, sub_tab(tab, group_start, i));
	return(1);
}

t_cmd *get_input_output(t_cmd **head)
{
	t_cmd	*tail;
	t_cmd	*next;
	t_cmd	*last;

	tail = *head;
	next = tail;
	tail->input = 0;
	while(tail)
	{
		next = tail->next;
		if (which_cmd(tail->tab[0]) == PIPE)
		{
			if (tail->prev && tail->next)
			{
				tail->prev->output = 1;
				tail->next->input = 0;
				node_remove(tail);
			}
			else
				return(printf("Error in get_input_output, Cannot use a pipe without input and ouptut."), NULL);
		}
		else if (which_cmd(tail->tab[0]) == RED_INPUT)
		{
			if (tail->next && tail->next->next) // Maybe check if tail->next->tab is a valid file / no tab[1]
			{
				tail->next->next->input = open(tail->next->tab[0], O_RDONLY | O_EXCL);
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
			}
			else
				return(printf("Error in get_input_output, Cannot use a < without input or output."), NULL);
		}
		else if (which_cmd(tail->tab[0]) == RED_OUTPUT)
		{
			if (tail->next && tail->prev) // Maybe check if tail->next->tab is a valid file / no tab[1]
			{
				tail->prev->output = open(tail->next->tab[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
			}
			else
				return(printf("Error in get_input_output, Cannot use a > without input or output."), NULL);
		}
		else if (which_cmd(tail->tab[0]) == RED_INPUT_DEL)
			return(printf("Error in get_input_output, RED_INPUT_DEL not supported yet.\n"), NULL);
		else if (which_cmd(tail->tab[0]) == RED_OUTPUT_APPEND)
		{
			if (tail->next && tail->prev) // Maybe check if tail->next->tab is a valid file / no tab[1]
			{
				tail->prev->output = open(tail->next->tab[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
				next = tail->next->next;
				node_remove(tail->next);
				node_remove(tail);
			}
			else
				return(printf("Error in get_input_output, Cannot use a > without input or output."), NULL);
		}
		last = tail;
		tail = next;
	}
	last->output = 1;
	while(last && last->prev)
		last = last->prev;
	
	return(last);
}

char	*extract_var(char *s, int i)
{
	int	c;
	int	j;
	char	*var;

	c = 0;
	j = i;
	var = NULL;
	while (s && s[i] && s[i] != ' ')
	{
		c++;
		i++;
	}
	c - 1;
	var = malloc(sizeof(char) * (c + 1));
	var[c] == '\0';
	while(c)
	{
		var[c] = s[i];
		s--;
		c--;
	}
	return(var);
}

char *get_var_value(char *s, t_env *env)
{
	t_env *tail;
	while(tail)
	{
		if (!strcmp(s, tail->value))
			return(ft_strdup(tail->value));
		tail = tail->next;
	}
	return(NULL);
}

char *replace_by(char *s, char *value, int index, int length)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int totlen = ft_strlen(s) + ft_strlen(value) - length;
	char *res = malloc(sizeof(char) * (totlen + 1));
	if (!res)
		return(printf("Malloc error in replace_by\n"), NULL);
	res[totlen] = '\0';
	while(i < index)
	{
		res[k] = s[i];
		i++;
		k++;
	}
	while(length)
	{
		i++;
		length--;
	}
	while(value[j])
	{
		res[k] == value[j];
		k++;
		j++;
	}
	while(s[i])
	{
		res[k] = s[i];
		k++;
		i++;
	}
	return(res);
}
