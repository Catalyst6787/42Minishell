/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:54:33 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/05 09:35:34 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_int_len(int n)
{
	unsigned int	i;
	unsigned int	nb;

	i = 0;
	if (n < 0)
	{
		nb = (unsigned int)-n;
		i = 1;
	}
	else
		nb = (unsigned int)n;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	ft_init_nb(int n)
{
	if (n < 0)
		return ((unsigned int)-n);
	return ((unsigned int)n);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	unsigned int	len;

	nb = ft_init_nb(n);
	len = ft_int_len(n);
	if (n == 0)
		len = 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (nb > 0)
	{
		str[len--] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		str[len] = '-';
	if (n == 0)
		str[len] = '0';
	return (str);
}

/*#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	int n = atoi(av[1]);
	printf("%s \n", ft_itoa(n));
	return (0);
}*/