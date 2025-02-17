/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:40:05 by lfaure            #+#    #+#             */
/*   Updated: 2025/02/17 16:15:11 by lfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	handle_sig_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	received_signal(signum);
}

void	init_signals_heredoc(void)
{
	signal(SIGINT, handle_sig_heredoc);
	signal(SIGQUIT, handle_sig_heredoc);
}

static int	setup(char *del, char **line, char **tot, int *sigint_received)
{
	int		is_single_quoted;
	char	*ndel;

	ndel = NULL;
	is_single_quoted = 0;
	init_signals_heredoc();
	received_signal(-1);
	if (is_quoted(del, 1, '\'') || is_quoted(del, 1, '\"'))
		is_single_quoted = 1;
	else
		is_single_quoted = 0;
	*line = readline(HEREDOC_PROMPT);
	if (received_signal(0) == SIGQUIT)
		*tot = ft_strdup("");
	else if (received_signal(0) == SIGINT)
		return (*sigint_received = 1, is_single_quoted);
	if (is_single_quoted)
	{
		ndel = malloc(sizeof(char) * (ft_strlen(del) - 1));
		ft_memcpy(ndel, del + 1, ft_strlen(del) - 2);
		ndel[ft_strlen(del) - 2] = '\0';
		del = ndel;
	}
	return (is_single_quoted);
}

static void	read_until_del(char **line, char **tot, char *del)
{
	char	*to_free;
	int		first;

	to_free = NULL;
	first = 1;
	while (*line && !received_signal(0) && ft_strcmp(*line, del))
	{
		if (!first)
		{
			to_free = *line;
			*line = ft_strjoin("\n", *line);
			free(to_free);
		}
		first = 0;
		to_free = *tot;
		*tot = ft_strjoin(*tot, *line);
		free(*line);
		*line = NULL;
		free(to_free);
		to_free = NULL;
		*line = readline(HEREDOC_PROMPT);
	}
}

char	**heredoc(char *del, t_env *env, int *sigint_received)
{
	int		is_single_quoted;
	char	*tot;
	char	*line;
	char	**result;

	tot = ft_strdup("");
	is_single_quoted = setup(del, &line, &tot, sigint_received);
	if (*sigint_received)
		return (NULL);
	read_until_del(&line, &tot, del);
	if (line)
		free(line);
	if (received_signal(0) == SIGINT)
		return (*sigint_received = 1, NULL);
	result = malloc(sizeof(char *) * 3);
	result[0] = ft_strdup("<<");
	if (!is_single_quoted)
		result[1] = expand_vars(tot, env, 1);
	else
		result[1] = tot;
	result[2] = NULL;
	return (result);
}
