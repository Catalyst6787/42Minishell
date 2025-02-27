/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:47:09 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/11 16:16:47 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_env	*create_env_node(char *name, char *value, int export)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	new->export = export;
	new->next = NULL;
	return (new);
}

t_env	*find_last_node(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	add_env_node(t_env **env, char *name, char *value, int export)
{
	t_env	*new;
	t_env	*last_node;

	new = create_env_node(name, value, export);
	last_node = find_last_node(*env);
	if (!last_node)
		*env = new;
	else
		last_node->next = new;
}

void	free_envp(t_env **env)
{
	t_env	*head;
	t_env	*tmp;

	head = *env;
	while (head)
	{
		tmp = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = tmp;
	}
}
