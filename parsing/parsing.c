/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:45:57 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/17 17:41:50 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	group_tokens(t_cmd **head, char **tab)
{
	int	i;
	int	group_has_tokens;
	int	group_start;

	i = 0;
	group_has_tokens = 0;
	group_start = 0;
	if (!tab || !tab[0])
		return (printf("Error: group_tokens encountered empty cmd\n"), 0);
	if (tab[0][i] == '<' || tab[0][i] == '>')
	{
		if (!tab[1])
			return (printf("Error: </>/>> expects file,%s",
					" << expects delimiter\n"), 0);
		append_node(head, sub_tab(tab, 0, 1));
		append_node(head, sub_tab(tab, 1, 2));
		i += 2;
		group_start = i;
	}
	group_has_tokens = group_tokens_loop(tab, head, &i, &group_start);
	if (group_has_tokens)
		append_node(head, sub_tab(tab, group_start, i));
	return (1);
}

char	*extract_var(char *s, int i)
{
	int		c;
	int		j;
	int		k;
	char	*var;

	c = 0;
	j = 0;
	var = NULL;
	i++;
	k = i;
	while (s && s[i] && s[i] != '\'' && s[i] != '\"' && s[i++] != ' ')
		c++;
	var = malloc(sizeof(char) * (c + 1));
	var[c] = '\0';
	i = k;
	while (c)
	{
		var[j] = s[i];
		j++;
		i++;
		c--;
	}
	return (var);
}

char	*get_var_value(char *s, t_env *env)
{
	while (env)
	{
		if (!strcmp(s, env->name))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*replace_by(char *s, char *value, int index, int length)
{
	int		i;
	int		j;
	int		k;
	int		totlen;
	char	*res;

	i = 0;
	j = 0;
	k = 0;
	totlen = ft_strlen(s) + ft_strlen(value) - length;
	res = malloc(sizeof(char) * (totlen + 1));
	if (!res)
		return (printf("Malloc error in replace_by\n"), NULL);
	res[totlen] = '\0';
	while (i < index)
		res[k++] = s[i++];
	i += length;
	while (value[j])
		res[k++] = value[j++];
	while (s[i])
		res[k++] = s[i++];
	free(s);
	s = NULL;
	return (free(value), value = NULL, res);
}
