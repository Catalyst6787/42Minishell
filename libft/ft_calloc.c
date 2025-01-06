/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:16:08 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/01 22:47:20 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ret;

	ret = (void *)malloc(count * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}

/*#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	size_t count = atoi(av[1]);
	size_t size = atoi(av[2]);
	char *ret = ft_calloc(count, size);
	size_t i = 0;
	while (i < count * size)
	{
		printf("%d", ret[i]);
		i++;
	}
	return (0);
}*/