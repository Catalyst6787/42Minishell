/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:46:40 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/17 17:53:20 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int	get_last_char(char *s, char c)
{
	int	i;

	i = ft_strlen(s);
	while (i != -1)
	{
		if (s[i] == c)
			return (i);
		i--;
	}
	return (printf("get_last_char did not found char, exiting"), exit(0), 0);
}

int	next_char(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	count_chars(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		printf("tab[%d]: {%s}\n", i, tab[i]);
		i++;
	}
}
