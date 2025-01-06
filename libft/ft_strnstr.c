/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:32:50 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/03 17:53:16 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (i + j < len && haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av)
{
	if (ac != 4)
		return (0);
	printf("ma fonction : %s \n", ft_strnstr(av[1], av[2], atoi(av[3])));
	printf("la vraie : %s \n", strnstr(av[1], av[2], atoi(av[3])));
	return (0);
}*/