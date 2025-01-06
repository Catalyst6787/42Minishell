/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:49:12 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/05 09:36:28 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_move(char *s1, char *set, int size, int choice)
{
	int	i;

	i = 0;
	if (choice == 0)
	{
		while (s1[i])
		{
			if (ft_is_set(s1[i], set) == 1)
				i++;
			else
				return (i);
		}
	}
	else if (choice == 1)
	{
		while (size > 0)
		{
			if (ft_is_set(s1[size - 1], set) == 1)
				size--;
			else
				return (size);
		}
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	end = 0;
	i = 0;
	while (s1[end])
		end++;
	start = ft_move((char *)s1, (char *)set, end, 0);
	end = ft_move((char *)s1, (char *)set, end, 1);
	ret = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!ret)
		return (NULL);
	while (start < end)
		ret[i++] = s1[start++];
	ret[i] = '\0';
	return (ret);
}

/*#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 3)
		return(0);
	printf("%s \n", ft_strtrim(av[1], av[2]));
	return(0);
}*/