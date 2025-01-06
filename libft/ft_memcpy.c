/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:13:14 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/03 18:45:03 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;
	size_t				i;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}

/*#include <stdio.h>
#include <string.h>

int main(void)
{
	char dst[] = "321456";
	char src[] = "123";
	size_t n = 3;
	ft_memcpy(dst, src, n);
	printf("ma fonction : %s \n", dst);

	char dst2[] = "321456";
	char src2[] = "123";
	memcpy(dst2, src2, n);
	printf("la vrai fonction : %s \n", dst2);
}*/