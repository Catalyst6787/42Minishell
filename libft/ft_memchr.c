/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:32:41 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/01 21:55:33 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	printf("ma fonction : %s \n", (char *)ft_memchr
	(av[1], atoi(av[2]), sizeof(av[1])));
	printf("la vraie : %s \n", (char *)memchr
	(av[1], atoi(av[2]), sizeof(av[1])));
	return (0);
}*/