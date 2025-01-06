/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:10:33 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/05 18:24:14 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start >= i)
	{
		ret = (char *)malloc(sizeof(char) * (1));
		if (!ret)
			return (NULL);
		ret[0] = '\0';
		return (ret);
	}
	if (len > i - start)
		len = i - start;
	i = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}

/*#include <stdio.h>

int main(int ac, char **av)
{
    if (ac != 4)
        return (0);
    char *s = av[1];
    int start = atoi(av[2]);
    int len = atoi(av[3]);
    printf("%s \n", ft_substr(s, start, len));
    return (0);
}*/