/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:01:49 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/11 16:16:42 by kgiraud          ###   ########.fr       */
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

void	change_value_in_envp(t_env *env, char *key,
	int size_key, char *new_value)
{
	while (env)
	{
		if (ft_strncmp(env->name, key, size_key) == 0)
		{
			free(env->value);
			env->value = new_value;
		}
		env = env->next;
	}
	return ;
}

void	delete_node(t_env *head, t_env *to_del)
{
	t_env	*tmp;

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

void	delete_export_node(t_env **env, char *key, int size_key)
{
	t_env	*head;
	t_env	*to_del;

	head = *env;
	to_del = get_in_envp(*env, key, size_key);
	if (!to_del)
		return ;
	if (to_del->export != 1)
		return ;
	if (head == to_del)
	{
		*env = (*env)->next;
		free(head->name);
		free(head->value);
		free(head);
		fgv_env(*env);
		return ;
	}
	delete_node(head, to_del);
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
			add_env_node(env, tmp[0], tmp[1], 1);
		else
			add_env_node(env, tmp[0], "", 1);
		ft_free_split(tmp);
	}
	add_env_node(env, "?", "0", 0);
	fgv_env(*env);
}
