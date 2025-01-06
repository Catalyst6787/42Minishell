/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:54:25 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/14 14:40:45 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_print_hex_adress(unsigned long nb, char *base, int *rs)
{
	if (nb > 15)
		ft_print_hex_adress(nb / 16, base, rs);
	if (*rs == -1)
		return ;
	ft_print_char(base[nb % 16], rs);
}

void	ft_print_ptr(void *ptr, char *base, int *rs)
{
	unsigned long	adress;

	adress = (unsigned long)ptr;
	ft_print_char('0', rs);
	if (*rs == -1)
		return ;
	ft_print_char('x', rs);
	if (*rs == -1)
		return ;
	if (!ptr)
	{
		ft_print_char('0', rs);
		return ;
	}
	ft_print_hex_adress(adress, base, rs);
}
