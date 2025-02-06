#include "../mini.h"


char *insert_space(char *s, int i) {
	if (!s)
		return(printf("string is NULL"), NULL);
	if (i < 0)
		return(printf("bad index"), NULL);
	int len = ft_strlen(s);
	char *new_str = (char *)malloc(len + 2); 
	if (!new_str) return NULL;

	int j = 0;
	while (j <= i) {
		new_str[j] = s[j];
		j++;
	}
	new_str[j] = ' ';
	j++;	
	while (j <= len) {
		new_str[j] = s[j - 1];
		j++;
	}
	new_str[j] = '\0';
		
	free(s);
	return new_str;
}


char	*insert_spaces(char *s)
{
	int i;

	i = 0;
	while(s[i])
	{
		if (s[i] && s[i + 1] && ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i + 1] == '>')))
		{
			if (i > 0 && s[i - 1] != ' ' && !is_quoted(s, i, '\'') && !is_quoted(s, i, '"'))
			{
				s = insert_space(s, i - 1);
				i = 0;
				continue ;
			}
			else if (s[i + 2] && s[i + 2] != ' ' && !is_quoted(s, i, '\'') && !is_quoted(s, i, '"'))
			{
				s = insert_space(s, i + 1);
				i = 0;
				continue ;
			}
		}
		else if (s[i] && (s[i] == '|' || (s[i] == '<' && (!s[i - 1] || s[i - 1] != '<' )) || (s[i] == '>' && (!s[i - 1] || s[i - 1] != '>' ))))
		{
			if (i > 0 && s[i - 1] != ' ' && !is_quoted(s, i, '\'') && !is_quoted(s, i, '"'))
			{
				s = insert_space(s, i - 1);
				i = 0;
				continue ;
			}
			else if (s[i + 1] && s[i + 1] != ' ' && !is_quoted(s, i, '\'') && !is_quoted(s, i, '"'))
			{
				s = insert_space(s, i);
				i = 0;
				continue ;
			}
		}
		i++;
	}
	return(s);
}


int	parse_input(char *line, t_cmd **groups, t_env *env)
{
	char	*clean_line;
	char **tab;

	clean_line = clean_input(ft_strdup(line));
	clean_line = remove_chars(clean_line, UNHANDLED);
	clean_line = expand_vars(clean_line, env);
	clean_line = insert_spaces(clean_line);
	if (!clean_line)
		return(groups = NULL, 0);
	tab = split_tokens(clean_line);
	if (group_tokens(groups, tab))
		*groups = get_input_output(groups, env);
	free(clean_line);
	clean_line = NULL;
	free(tab);
	tab = NULL;
	reset_id(*groups);
	return(1);
}

char *clean_quotes(char *s, int *is_changed)
{
	int simple_isopen;
	int	double_isopen;
	int i;

	simple_isopen = 0;
	double_isopen = 0;
	i = 0;
	*is_changed = 0;

	while(s[i])
	{
		if (s[i] == '"' && !simple_isopen)
		{
			if (double_isopen)
				double_isopen = 0;
			else
				double_isopen = 1;
		}
		else if (s[i] == '\'' && !double_isopen)
		{
			if (simple_isopen)
				simple_isopen = 0;
			else
				simple_isopen = 1;
		}
		i++;
	}
	if (simple_isopen)
	{
		s = remove_lone_quote_specify(s, '\'');
		*is_changed = 1;
	}
	if (double_isopen)
	{
		s = remove_lone_quote_specify(s, '"');
		*is_changed = 1;
	}
	return(s);
}

char *clean_useless_quotes(char *s)
{
	int simple_isopen;
	int	double_isopen;
	int i;

	simple_isopen = 0;
	double_isopen = 0;
	i = 0;

	while(s[i])
	{
		if (s[i] == '"' && !simple_isopen)
		{
			if (s[i + 1] && s[i + 1] == '\"')
			{
				s = rem_char(s, i);
				s = rem_char(s, i);
				i = 0;
				continue;
			}
			else if (double_isopen)
				double_isopen = 0;
			else
				double_isopen = 1;
		}
		else if (s[i] == '\'' && !double_isopen)
		{
			if (s[i + 1] && s[i + 1] == '\'')
			{
				s = rem_char(s, i);
				s = rem_char(s, i);
				i = 0;
				continue;
			}
			else if (simple_isopen)
				simple_isopen = 0;
			else
				simple_isopen = 1;
		}
		i++;
	}
	return(s);
}

char *remove_chars(char *s, char *chars)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(s[i])
	{
		while(chars[j])
		{
			if (s[i] == chars[j] && !is_quoted(s, i, '\'') && !is_quoted(s, i, '\"'))
			{
				s = rem_char(s, i);
				i = 0;
				j = 0;
				continue;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return(s);
}

char *expand_vars(char *s, t_env *env)
{
	int i;
	char *var;
	char *var_value;

	i = 0;
	var = NULL;
	var_value = NULL;
	while (s[i])
	{
		if (s[i] == '$' && !is_quoted(s, i, '\''))
		{
			var = extract_var(s, i);
			var_value = get_var_value(var, env);
			if (var_value)
				s = replace_by(s, var_value, i, (ft_strlen(var) + 1));
			else
				s = replace_by(s, ft_strdup(""), i, (ft_strlen(var) + 1));
			free(var);

		}
		i++;
	}
	return(s);
}
