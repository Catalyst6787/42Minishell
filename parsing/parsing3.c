/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:45:57 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/17 17:42:20 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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
	int		i;
	int		t;
	char	*dup;

	i = 0;
	t = 0;
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

static void	split_tokens_loop(char **s, int *i, int *j, char ***tab)
{
	while ((*s)[*i])
	{
		if ((*s)[*i] == ' ')
			(*i)++;
		else if (*j > 0 && which_cmd((*tab)[*j - 1]) == RED_INPUT_DEL
			&& (*s)[*i + 1] && (is_quoted(*s, *i + 1, '\'')
				|| is_quoted(*s, *i + 1, '\"')))
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
