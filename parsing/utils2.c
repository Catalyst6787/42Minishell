/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:46:40 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/17 17:52:50 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	which_cmd_extra(char *cmd)
{
	if (!ft_strcmp(cmd, ">>"))
		return (RED_OUTPUT_APPEND);
	else if (!ft_strcmp(cmd, "&&"))
		return (AND);
	else if (!ft_strcmp(cmd, "||"))
		return (OR);
	else if (!ft_strcmp(cmd, "("))
		return (PAR_OPEN);
	else if (!ft_strcmp(cmd, ")"))
		return (PAR_CLOSE);
	else
		return (EXTERNAL);
}

int	which_cmd(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	else if (!ft_strcmp(cmd, "cd"))
		return (CD);
	else if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	else if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	else if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	else if (!ft_strcmp(cmd, "env"))
		return (ENV);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	else if (!ft_strcmp(cmd, "|"))
		return (PIPE);
	else if (!ft_strcmp(cmd, "<"))
		return (RED_INPUT);
	else if (!ft_strcmp(cmd, ">"))
		return (RED_OUTPUT);
	else if (!ft_strcmp(cmd, "<<"))
		return (RED_INPUT_DEL);
	else
		return (which_cmd_extra(cmd));
}

int	is_special(char c)
{
	if (c == '<' || c == '>')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '$')
		return (1);
	else if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int	is_separator(char *s)
{
	if ((ft_strlen(s) == 1 || (ft_strlen(s) == 2 && s[0] == s[1]))
		&& (s[0] == '|' || s[0] == '>' || s[0] == '<'))
		return (1);
	else if (ft_strlen(s) == 2 && s[0] == s[1] && s[0] == '&')
		return (1);
	else
		return (0);
}

int	next_separator(char **tab, int i)
{
	while (tab[i])
	{
		if (is_separator(tab[i]))
			return (i);
		i++;
	}
	return (0);
}
