/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:35:11 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/13 17:35:12 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	clean_useless_quotes_double(char **s, int *i, int *double_isopen)
{
	if (*double_isopen)
		*double_isopen = 0;
	else if ((*s)[*i + 1] && (*s)[*i + 1] == '\"')
	{
		*s = rem_char(*s, *i);
		*s = rem_char(*s, *i);
		*i = 0;
		return (1);
	}
	else
		*double_isopen = 1;
	return (0);
}

static int	clean_useless_quotes_simple(char **s, int *i, int *simple_isopen)
{
	if (*simple_isopen)
		*simple_isopen = 0;
	else if ((*s)[*i + 1] && ((*s)[*i + 1] == '\''))
	{
		*s = rem_char(*s, *i);
		*s = rem_char(*s, *i);
		*i = 0;
		return (1);
	}
	else
		*simple_isopen = 1;
	return (0);
}

char	*clean_useless_quotes(char *s)
{
	int	simple_isopen;
	int	double_isopen;
	int	i;

	simple_isopen = 0;
	double_isopen = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' && !simple_isopen
			&& clean_useless_quotes_double(&s, &i, &double_isopen))
			continue ;
		else if (s[i] == '\'' && !double_isopen
			&& clean_useless_quotes_simple(&s, &i, &simple_isopen))
			continue ;
		i++;
	}
	return (s);
}
