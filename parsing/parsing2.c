/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:40:13 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/17 17:42:11 by lfaure           ###   ########.fr       */
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
		if ((s[i] == '\'' && s[i + 1] == '\'')
			|| (s[i] == '\"' && s[i + 1] == '\"'))
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

char	*remove_lone_quote_specify(char *s, char c, int *is_changed)
{
	s = rem_char(s, get_last_char(s, c));
	*is_changed = 1;
	return (s);
}

char	*clean_input(char *s)
{
	int	is_changed;

	is_changed = 1;
	while (is_changed)
		s = clean_quotes(s, &is_changed);
	s = clean_useless_quotes(s);
	return (s);
}
