/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:36:50 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/14 14:40:53 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_print_string(char *s, int *rs)
{
	if (!s)
	{
		ft_print_string("(null)", rs);
		return ;
	}
	while (*s)
	{
		if (*rs == -1)
			return ;
		ft_print_char(*s, rs);
		s++;
	}
}
