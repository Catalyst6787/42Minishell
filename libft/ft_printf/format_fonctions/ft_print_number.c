/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:16:08 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/14 14:40:40 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_print_number(int n, int *rs)
{
	long	nb;

	nb = (long)n;
	if (n < 0)
	{
		ft_print_char('-', rs);
		nb = (long)-nb;
	}
	if (nb > 9)
		ft_print_number(nb / 10, rs);
	if (*rs == -1)
		return ;
	ft_print_char(nb % 10 + '0', rs);
}
