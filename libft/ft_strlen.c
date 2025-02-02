/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:07:27 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/29 12:18:39 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

/*#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	const char *s = av[1];
	printf("ma fonction : %zu\n", ft_strlen(s));
	printf("la vraie : %zu\n", ft_strlen(s));
	return (0);
}*/