/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:33:15 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/13 17:33:22 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	check_input(char *s, int i)
{
	if (!s)
		return (0);
	if (i < 0)
		return (0);
	return (1);
}

char	*insert_space(char *s, int i)
{
	int		len;
	int		j;
	char	*new_str;

	j = 0;
	if (!check_input(s, i))
		return (NULL);
	len = ft_strlen(s);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	while (j <= i)
	{
		new_str[j] = s[j];
		j++;
	}
	new_str[j] = ' ';
	j++;
	while (j <= len)
	{
		new_str[j] = s[j - 1];
		j++;
	}
	new_str[j] = '\0';
	return (free(s), new_str);
}

static	int	insert_space_before(char **s, int *i)
{
	if (*i > 0 && (*s)[*i - 1] != ' '
		&& !is_quoted(*s, *i, '\'') && !is_quoted(*s, *i, '"'))
	{
		*s = insert_space(*s, *i - 1);
		*i = 0;
		return (1);
	}
	else if ((*s)[*i + 2] && (*s)[*i + 2] != ' '
		&& !is_quoted(*s, *i, '\'') && !is_quoted(*s, *i, '"'))
	{
		*s = insert_space(*s, *i + 1);
		*i = 0;
		return (1);
	}
	return (0);
}

static int	insert_space_after(char **s, int *i)
{
	if (*i > 0 && (*s)[*i - 1] != ' '
		&& !is_quoted(*s, *i, '\'') && !is_quoted(*s, *i, '"'))
	{
		*s = insert_space(*s, *i - 1);
		*i = 0;
		return (1);
	}
	else if ((*s)[*i + 1] && (*s)[*i + 1] != ' '
		&& !is_quoted(*s, *i, '\'') && !is_quoted(*s, *i, '"'))
	{
		*s = insert_space(*s, *i);
		*i = 0;
		return (1);
	}
	return (0);
}

char	*insert_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i + 1] && ((s[i] == '<' && s[i + 1] == '<')
				|| (s[i] == '>' && s[i + 1] == '>')))
		{
			if (insert_space_before(&s, &i))
				continue ;
		}
		else if (s[i]
			&& (s[i] == '|' || (s[i] == '<' && (!s[i - 1] || s[i - 1] != '<' ))
				|| (s[i] == '>' && (!s[i - 1] || s[i - 1] != '>' ))))
		{
			if (insert_space_after(&s, &i))
				continue ;
		}
		i++;
	}
	return (s);
}
