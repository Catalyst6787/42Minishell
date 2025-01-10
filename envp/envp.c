/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:01:49 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/10 16:57:20 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_env	*get_in_envp(t_env *env, char *key, int size_key)
{
	while (env)
	{
		if (ft_strncmp(env->name, key, size_key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	change_value_in_envp(t_env *env, char *key, int size_key, char *new_value)
{
	while (env)
	{
		if (ft_strncmp(env->name, key, size_key) == 0)
			env->value = ft_strdup(new_value);
		env = env->next;
	}
	return ;
}

void	delete_export_node(t_env **env, char *key, int size_key)
{
	t_env	*head;
	t_env	*tmp;
	t_env	*to_del;

	head = *env;
	to_del = get_in_envp(*env, key, size_key);
	if (to_del->export != 1)
		return ;
	if (head == to_del)
	{
		*env = (*env)->next;
		free(head->name);
		free(head->value);
		free(head);
		return ;
	}
	while (head)
	{
		if (head->next == to_del)
		{
			tmp = head->next->next;
			free(head->next->name);
			free(head->next->value);
			free(head->next);
			head->next = tmp;
			return ;
		}
		head = head->next;
	}
}

void	init_envp(t_env **env, char **envp)
{
	int		i;
	char	**tmp;

	i = -1;
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (!tmp)
		{
			perror("minishell: init env error");
			return ;
		}
		if (tmp[1])
			add_env_node(env, tmp[0], tmp[1], 0);
		else
			add_env_node(env, tmp[0], "", 0);
		ft_free_split(tmp);
	}
}
