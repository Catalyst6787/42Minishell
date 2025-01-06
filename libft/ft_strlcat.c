/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:49:15 by kgiraud           #+#    #+#             */
/*   Updated: 2024/09/29 17:22:48 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	ret;

	i = 0;
	j = 0;
	while (src[i])
		i++;
	while (dst[j] && j < dstsize)
		j++;
	ret = i + j;
	i = 0;
	if (dstsize == 0)
		return (ret);
	if (j == dstsize)
		return (ret);
	while (j < dstsize - 1 && src[i])
		dst[j++] = src[i++];
	if (j < dstsize)
		dst[j] = '\0';
	return (ret);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	size_t dstsize = 11;
	char dst[11] = "salut";
	char src[] = ", mec";
	ft_strlcat(dst, src, dstsize);
	printf("%s \n", dst);

	char dst2[11] = "salut";
	strlcat(dst2, src, dstsize);
	printf("%s \n", dst2);
	return (0);
}*/