/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:08:58 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/29 14:51:44 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)b;
	while (i < len)
		p[i++] = (unsigned char)c;
	return (p);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	size_t len = atoi(av[2]);
	unsigned char *b = malloc(sizeof(unsigned char) * (len));
	int c = atoi(av[1]);
	ft_memset(b, c, len);
	size_t i = 0;
	printf("ma fonction :\n");
	while (i < len)
		printf("%c", b[i++]);
	printf("\n");
	i = 0;
	memset(b, 0, len);
	memset(b, c, len);
	printf("la vrai fonction :\n");
	while (i < len)
		printf("%c", b[i++]);
	return (0);
}*/