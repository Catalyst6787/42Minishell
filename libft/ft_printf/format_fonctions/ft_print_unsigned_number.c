/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_number.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:33:58 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/14 14:41:03 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_print_unsigned_number(unsigned int nb, int *rs)
{
	if (nb > 9)
		ft_print_unsigned_number(nb / 10, rs);
	if (*rs == -1)
		return ;
	ft_print_char(nb % 10 + '0', rs);
}
