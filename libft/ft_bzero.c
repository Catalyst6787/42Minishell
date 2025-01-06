/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:56:27 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/29 14:49:29 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*res;
	size_t			i;

	res = (unsigned char *)s;
	i = 0;
	while (i < n)
		res[i++] = 0;
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	size_t n = atoi(av[1]);
	unsigned char *s = malloc(sizeof(unsigned char) * (n));
	ft_bzero(s, n);
	size_t i = 0;
	printf("ma fonction :\n");
	while (i < n)
		printf("%hhu", s[i++]);
	printf("\n");
	i = 0;
	bzero(s, n);
	bzero(s, n);
	printf("la vraie fonction :\n");
	while (i < n)
		printf("%hhu", s[i++]);
	return (0);
}*/