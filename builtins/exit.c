/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:28:00 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/17 14:47:28 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	fgv_exit_arg(int new)
{
	static int	value;

	if (new == -1)
		return (value);
	value = new;
	return (value);
}

int	is_all_digits(char *s)
{
	if (!s)
		return (-1);
	if (*s == '+')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	ft_exit(char **av, t_env *env)
{
	if (av[1] && av[2])
	{
		printf("minishell: exit: too many arguments\n");
		if (is_all_digits(av[1]))
		{
			change_value_in_envp(env, "?", 1, ft_strdup("1"));
			return (1);
		}
		fgv_exit_arg(2);
	}
	else if (av[1])
	{
		if (is_all_digits(av[1]))
			fgv_exit_arg(ft_atoi(av[1]));
		else
		{
			printf("minishell: exit: int expected\n");
			fgv_exit_arg(2);
		}
	}
	return (0);
}
