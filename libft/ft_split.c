/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:22:08 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/06 22:05:26 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s, char c)
{
	int	nb_w;
	int	in_words;

	nb_w = 0;
	in_words = 0;
	while (*s)
	{
		if (*s != c && in_words == 0)
		{
			in_words = 1;
			nb_w++;
		}
		else if (*s == c)
			in_words = 0;
		s++;
	}
	return (nb_w);
}

int	ft_count_char(char const *s, char c)
{
	int	nb_c;

	nb_c = 0;
	while (*s && *s == c)
		s++;
	while (*s && *s != c)
	{
		nb_c++;
		s++;
	}
	return (nb_c);
}

void	ft_free(char **tab, int nb_w)
{
	int	i;

	i = 0;
	while (i < nb_w && tab[i])
		free(tab[i++]);
	free(tab);
}

int	ft_star_to_stars(char **tab, char const *s, char c, int nb_w)
{
	int	word;
	int	i;

	word = 0;
	while (word < nb_w)
	{
		while (*s && *s == c)
			s++;
		tab[word] = (char *)malloc(sizeof(char) * (ft_count_char(s, c) + 1));
		if (!tab[word])
		{
			ft_free(tab, word);
			return (0);
		}
		i = 0;
		while (*s && *s != c)
		{
			tab[word][i++] = *s;
			s++;
		}
		tab[word][i] = '\0';
		word++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nb_w;

	if (!s)
		return (NULL);
	nb_w = ft_count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_w + 1));
	if (!tab)
		return (NULL);
	if (!ft_star_to_stars(tab, s, c, nb_w))
		return (NULL);
	tab[nb_w] = NULL;
	return (tab);
}

/*#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	char **tab = ft_split(av[1], av[2][0]);
	int i = 0;
	int count = ft_count_words(av[1], av[2][0]);
	while (i < count)
		printf("%s \n", tab[i++]);
	return (0);
}*/