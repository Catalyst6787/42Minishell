/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:05:42 by kgiraud           #+#    #+#             */
/*   Updated: 2024/10/14 14:42:02 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_format_fonctions(char c, va_list *va, int *rs)
{
	if (c == 'c')
		ft_print_char((char)va_arg(*va, int), rs);
	else if (c == 's')
		ft_print_string(va_arg(*va, char *), rs);
	else if (c == 'p')
		ft_print_ptr(va_arg(*va, void *), "0123456789abcdef", rs);
	else if (c == 'd' || c == 'i')
		ft_print_number(va_arg(*va, int), rs);
	else if (c == 'u')
		ft_print_unsigned_number(va_arg(*va, unsigned int), rs);
	else if (c == 'x' || c == 'X')
	{
		if (c == 'x')
			ft_print_hex(va_arg(*va, unsigned int), "0123456789abcdef", rs);
		if (c == 'X')
			ft_print_hex(va_arg(*va, unsigned int), "0123456789ABCDEF", rs);
	}
	else if (c == '%')
		ft_print_char(c, rs);
}

int	ft_printf(const char *s, ...)
{
	va_list	va;
	int		rs;

	va_start(va, s);
	rs = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (*s)
				ft_format_fonctions(*s, &va, &rs);
		}
		else
			ft_print_char(*s, &rs);
		if (rs == -1)
		{
			va_end(va);
			return (rs);
		}
		s++;
	}
	va_end(va);
	return (rs);
}

/*#include <stdio.h>
int	main(void)
{
	int a;
	int b;

	a = ft_printf("%c %c %c \n", '0', 0, '1');
	b = printf("%c %c %c \n", '0', 0, '1');
	printf("a : %d \nb : %d \n", a, b);
	return (0);
}*/