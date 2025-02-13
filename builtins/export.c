/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:06:59 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/13 15:19:58 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	var_is_valid(char *s)
{
	int	i;

	i = 1;
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export(t_env *env)
{
	while (env)
	{
		if (env->export)
		{
			printf("declare -x %s=\"", env->name);
			printf("%s\"\n", env->value);
		}
		env = env->next;
	}
}

int	ft_export(char **av, t_env *env)
{
	char	**tab_var;
	t_env	*var;

	if (!av[1])
		print_export(env);
	else if (av[1])
	{
		tab_var = ft_split(av[1], '=');
		if (!tab_var)
			return (perror("minishell: spit error in export"), 1);
		if (!var_is_valid(tab_var[0]))
			return (perror("minishell: export: not a valid identifier"), 1);
		var = get_in_envp(env, tab_var[0], ft_strlen(tab_var[0]));
		if (var)
		{
			free(var->value);
			var->value = ft_strdup(tab_var[1]);
			if (!var->value)
				return (perror("minishell: strdup error in export"), 1);
		}
		else
			add_env_node(&env, tab_var[0], tab_var[1], 1);
		ft_free_split(tab_var);
	}
	return (0);
}
