/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:56:24 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/05 09:36:20 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned	int, char))
{
	int		i;
	char	*ret;

	i = 0;
	if (!s || !f)
		return (NULL);
	while (s[i])
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (s[++i])
		ret[i] = f(i, s[i]);
	ret[i] = '\0';
	return (ret);
}

/*char change_case(unsigned int index, char c)
{
	(void)index;
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

#include <stdio.h>
#include <ctype.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	printf("%s", ft_strmapi(av[1], change_case));
	return (0);
}*/