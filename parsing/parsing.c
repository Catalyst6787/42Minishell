/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:45:57 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/13 18:12:23 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// remove char at s[i], frees original s and returns updated string
char	*rem_char(char *s, int t)
{
	int		i;
	int		j;
	char	*nstr;

	nstr = malloc(sizeof(char) * ft_strlen(s));
	nstr[ft_strlen(s) - 1] = '\0';
	i = 0;
	j = 0;
	while (s[j])
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
	return (nstr);
}

char	*remove_useless_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i + 1])
	{
		if ((s[i] == '\'' && s[i + 1] == '\'') || (s[i] == '\"' && s[i + 1] == '\"'))
		{
			s = rem_char(s, i);
			s = rem_char(s, i);
			i = 0;
		}
		i++;
	}
	return (s);
}

char	*remove_lone_quotes(char *s)
{
	if ((count_chars(s, '\'') % 2) != 0)
		s = rem_char(s, get_last_char(s, '\''));
	if ((count_chars(s, '\"') % 2) != 0)
		s = rem_char(s, get_last_char(s, '\"'));
	return (s);
}

char *remove_lone_quote_specify(char *s, char c, int *is_changed)
{
	s = rem_char(s, get_last_char(s, c));
	*is_changed = 1;
	return (s);
}



char	*clean_input(char *s)
{
	int is_changed;
	is_changed = 1;

	while(is_changed)
		s = clean_quotes(s, &is_changed);
	s = clean_useless_quotes(s);
	return (s);
}

int	end_of_token(char *s, int is_quoted_heredoc)
{
	if (isquote(s[0]) && !is_quoted_heredoc)
		return (next_char(s, s[0]));
	else
		return (next_char(s, ' '));
}

char	*token_dup(char *s, int is_quoted_heredoc)
{
	int		i;
	int		t;
	char	*dup;

	i = 0;
	t = 0;
	t = end_of_token(s, is_quoted_heredoc);
	dup = malloc(sizeof(char) * t + 1);
	dup[t] = '\0';
	while (i < t)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

char	*quoted_token_dup(char *s)
{
	int i;
	int t;

	i = 0;
	t = 0;
	char *dup;
	t = end_of_token(s, 0);
	dup = malloc(sizeof(char) * t);
	dup[t - 1] = '\0';
	while (i < t - 1)
	{
		dup[i] = s[i + 1];
		i++;
	}
	return (dup);
}

static void split_tokens_loop(char **s, int *i, int *j, char ***tab)
{
	while ((*s)[*i])
	{
		if ((*s)[*i] == ' ')
			(*i)++;
		else if (*j > 0 && which_cmd((*tab)[*j - 1]) == RED_INPUT_DEL
			&& (*s)[*i + 1] && (is_quoted(*s, *i + 1, '\'') || is_quoted(*s, *i + 1, '\"')))
		{
			(*tab)[*j] = token_dup(*s + *i, 1);
			*i = end_of_token(*s + *i, 1) + *i;
			(*j)++;
		}
		else if (isquote((*s)[*i]))
		{
			(*tab)[*j] = quoted_token_dup(*s + *i);
			*i = end_of_token(*s + *i, 0) + *i + 1;
			(*j)++;
		}
		else
		{
			(*tab)[*j] = token_dup(*s + *i, 0);
			*i = end_of_token(*s + *i, 0) + *i;
			(*j)++;
		}
	}
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
	split_tokens_loop(&s, &i, &j, &tab);
	return (tab);
}

int	count_tokens(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i++;
		else if (isquote(s[i]))
		{
			i = end_of_token(s + i, 0) + i + 1;
			c++;
		}
		else
		{
			i = end_of_token(s + i, 0) + i;
			c++;
		}
	}
	return (c);
}

void	append_node(t_cmd **head, char **tab)
{
	t_cmd	*last;
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (printf("Malloc error in append_node(), exiting"), exit(0)); // Should free_all
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
		while (last->next)
			last = last->next;
		new->id = last->id + 1;
		last->next = new;
		new->prev = last;
	}
	new->input = 0;
	new->output = 1;
}

void append_node_before(t_cmd **tail, char **tab, t_cmd **head)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (printf("Malloc error in append_node_before(), exiting\n"), exit(1));
	new->tab = tab;
	new->id = 0;
	new->input = 0;
	new->output = 1;
	if (*tail)
	{
		new->next = *tail;
		new->prev = (*tail)->prev;
		(*tail)->prev = new;
		if (new->prev)
			new->prev->next = new;
	}
	else
	{
		new->next = NULL;
		new->prev = NULL;
		*head = *tail = new;
	}
	if (*tail == *head)
		*head = *tail;
}


char **sub_tab(char **tab, int from, int to)
{
	char	**subtab;
	int		size;
	int		i;

	i = 0;
	if (!tab)
		return (printf("sub_tab was sent bad params, returning NULL"), NULL);
	size = to - from;
	subtab = malloc(sizeof(char *) * (size + 1));
	subtab[size] = NULL;
	while (i < size)
	{
		subtab[i] = tab[from];
		i++;
		from++;
	}
	return (subtab);
}

static int	group_tokens_loop(char **tab, t_cmd **head, int *i, int *group_start)
{
	int group_has_tokens = 0;
	while (tab[*i])
	{
		if (is_separator(tab[*i]) && group_has_tokens)
		{
			append_node(head, sub_tab(tab, *group_start, *i));
			append_node(head, sub_tab(tab, *i + 0, *i + 1));
			(*i)++;
			*group_start = *i;
			group_has_tokens = 0;
		}
		else
		{
			(*i)++;
			group_has_tokens = 1;
		}	
	}
	return (group_has_tokens);
}

int	group_tokens(t_cmd **head, char **tab)
{
	int	i;
	int	group_has_tokens;
	int	group_start;

	i = 0;
	group_has_tokens = 0;
	group_start = 0;
	if (!tab || !tab[0])
		return (printf("Error: group_tokens encountered empty cmd\n"), 0);
	if (tab[0][i] == '<' || tab[0][i] == '>')
	{
		if (!tab[1])
			return (printf("Error: </>/>> Must be followed by input file, << must be followed by delimiter,\n"), 0);
		append_node(head, sub_tab(tab, 0, 1));
		append_node(head, sub_tab(tab, 1, 2));
		i += 2;
		group_start = i;
	}
	group_has_tokens = group_tokens_loop(tab, head, &i, &group_start);
	if (group_has_tokens)
		append_node(head, sub_tab(tab, group_start, i));
	return (1);
}



char	*extract_var(char *s, int i)
{
	int c;
	int j;
	int k;
	char *var;

	c = 0;
	var = NULL;
	i++;
	j = 0;
	k = i;
	while(s && s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != ' ')
	{
		c++;
		i++;
	}
	var = malloc(sizeof(char) * (c + 1));
	var[c] = '\0';
	i = k;
	while(c)
	{
		var[j] = s[i];
		j++;
		i++;
		c--;
	}
	return(var);
}

char *get_var_value(char *s, t_env *env)
{
	while(env)
	{
		if (!strcmp(s, env->name))
			return(ft_strdup(env->value));
		env = env->next;
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
		res[k] = value[j];
		k++;
		j++;
	}
	while(s[i])
	{
		res[k] = s[i];
		k++;
		i++;
	}
	free(s);
	s = NULL;
	free(value);
	value = NULL;
	return(res);
}
