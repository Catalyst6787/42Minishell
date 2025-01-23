#include "../mini.h"

int	parse_input(char *line, t_cmd **groups, t_env *env)
{
	char *clean_line;
	char **tab;

	clean_line = clean_input(ft_strdup(line));
	clean_line = expand_vars(clean_line, env);
	if (!clean_line)
		return(groups = NULL, 0);
	tab = split_tokens(clean_line);
	if (group_tokens(groups, tab))
		*groups = get_input_output(groups);
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
			if (!var_value)
				return(printf("Error: variable '%s' not found\n", var), NULL);
			s = replace_by(s, var_value, i, (ft_strlen(var) + 1));
		}
		i++;
	}
	return(s);
}
