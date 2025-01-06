/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:50:23 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/05 09:36:06 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ret;

	i = 0;
	while (s1[i])
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	while (i >= 0)
	{
		ret[i] = s1[i];
		i--;
	}
	return (ret);
}

/*#include <stdio.h>
#include <string.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	printf("ma fonction : %s \n", ft_strdup(av[1]));
	printf("la vraie : %s \n", strdup(av[1]));
	return (0);
}*/