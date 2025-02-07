/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:38:36 by kgiraud           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/07 14:35:50 by kgiraud          ###   ########.fr       */
=======
/*   Updated: 2025/02/07 16:37:56 by lfaure           ###   ########.fr       */
>>>>>>> lfaure
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

// Dans le parent (minishell) :
// Ctrl-C ne doit pas tuer le shell, mais afficher un nouveau prompt.
// Ctrl-\ doit être ignoré.
// Ctrl-D doit fermer le shell (EOF sur l’entrée standard).

// Dans les enfants (les commandes) :
// Ctrl-C doit tuer l’enfant s’il est en cours d’exécution.
// Ctrl-\ doit tuer l’enfant ou avoir son comportement par défaut.

int fgv_in_cmd(int new)
{
	static int value;
	
	if (new == -1)
		return (value);
	value = new;
	return (value);
}

int fgv_sig_nb(int new)
{
	static int value;
	
	if (new == -1)
		return (value);
	value = new;
	return (value);
}

t_env	*fgv_env(t_env *new)
{
	static t_env *env;
	
	if (!new)
		return (env);
	env = new;
	return (env);
}

void	handle_signint(int sig)
{
	(void)sig;
	printf("\n");
	if (!fgv_in_cmd(-1))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		change_value_in_envp(fgv_env(NULL), "?", 1, ft_strdup("130"));
	}
	else
	{
		fgv_sig_nb(130);
	}
}

void	handle_signals(void)
{
	signal(SIGINT, handle_signint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	//signal(SIGQUIT, SIG_DFL);
}