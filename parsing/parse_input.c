/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:26:09 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/13 17:34:36 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	parse_input(char *line, t_cmd **groups, t_env *env)
{
	char	*clean_line;
	char	**tab;

	clean_line = clean_input(ft_strdup(line));
	clean_line = remove_chars(clean_line, UNHANDLED);
	clean_line = expand_vars(clean_line, env, 0);
	clean_line = insert_spaces(clean_line);
	if (!clean_line)
		return (groups = NULL, 0);
	tab = split_tokens(clean_line);
	if (group_tokens(groups, tab))
		*groups = get_input_output(groups, env);
	free(clean_line);
	clean_line = NULL;
	free(tab);
	tab = NULL;
	reset_id(*groups);
	return (1);
}

char	*clean_quotes(char *s, int *is_changed)
{
	int	simple_isopen;
	int	double_isopen;
	int	i;

	simple_isopen = 0;
	double_isopen = 0;
	i = 0;
	*is_changed = 0;
	while (s[i])
	{
		if (s[i] == '"' && !simple_isopen && double_isopen)
			double_isopen = 0;
		else if (s[i] == '"' && !simple_isopen)
			double_isopen = 1;
		else if (s[i] == '\'' && !double_isopen && simple_isopen)
			simple_isopen = 0;
		else if (s[i] == '\'' && !double_isopen)
			simple_isopen = 1;
		i++;
	}
	if (simple_isopen)
		s = remove_lone_quote_specify(s, '\'', is_changed);
	if (double_isopen)
		s = remove_lone_quote_specify(s, '"', is_changed);
	return (s);
}

char	*remove_chars(char *s, char *chars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (chars[j])
		{
			if (s[i] == chars[j]
				&& !is_quoted(s, i, '\'') && !is_quoted(s, i, '\"'))
			{
				s = rem_char(s, i);
				i = 0;
				j = 0;
				continue ;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (s);
}

char	*expand_vars(char *s, t_env *env, int is_heredoc)
{
	int		i;
	char	*var;
	char	*var_value;

	i = 0;
	var = NULL;
	var_value = NULL;
	while (s[i])
	{
		if (s[i] == '$' && (!is_quoted(s, i, '\'') || is_heredoc))
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
	return (s);
}
