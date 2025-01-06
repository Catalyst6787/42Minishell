/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:52:00 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/29 14:52:04 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == 0)
		return (src_len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

/*#include <stdio.h>
#include <string.h>

int	main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	char *dst = av[1];
	char *src = av[2];
	ft_strlcpy(dst, src, strlen(dst) + 1);
	printf("%s \n", dst);

	char *dst2 = av[1];
	char *src2 = av[2];
	strlcpy(dst2, src2, strlen(dst) + 1);
	printf("%s \n", dst2);

	return (0);
}*/