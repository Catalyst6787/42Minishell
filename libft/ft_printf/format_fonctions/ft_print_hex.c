/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:40:15 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/14 14:40:36 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_print_hex(unsigned int nb, char *base, int *rs)
{
	if (nb > 15)
		ft_print_hex(nb / 16, base, rs);
	if (*rs == -1)
		return ;
	ft_print_char(base[nb % 16], rs);
}
