/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:51:31 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/03 19:00:52 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	i = 0;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (source < dest)
	{
		while (len-- > 0)
			dest[len] = source[len];
	}
	else
	{
		while (len > 0)
		{
			dest[i] = source[i];
			len--;
			i++;
		}
	}
	return (dst);
}

/*#include <stdio.h>
#include <string.h>

int main(void)
{
	char src[] = "123456789";
	size_t n = 1;
	char *o = ft_memmove(src + 4, src, n);
	printf("ma fonction : %s \n", o);

	char src2[] = "123456789";
	char *o2 = memmove(src + 4, src2, n);
	printf("la vrai fonction : %s \n", o2);
	return (0);
}*/