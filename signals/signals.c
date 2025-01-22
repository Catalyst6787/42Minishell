/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:38:36 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/22 15:51:33 by kgiraud          ###   ########.fr       */
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

void	handle_signint(int sig)
{
	(void)sig;
	//printf("Là ça signint\n");
	rl_on_new_line();
	rl_replace_line("", 0); // ça peut etre ça marche pas
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	handle_signals(void)
{
	signal(SIGINT, handle_signint);
	signal(SIGQUIT, handle_sigquit);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}