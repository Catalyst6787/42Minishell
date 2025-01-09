/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:58:49 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/09 14:53:13 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_cd(char **av, char **envp)
{
	// Garder le répertoire courant dans $OLDPWD avec getcwd()
	// Si échec de getcwd, afficher une erreur et quitter

	// Déterminer le changement de répertoire :
	// - Rien : utiliser $HOME
	// - "-" : utiliser $OLDPWD
	// - Sinon : utiliser le path donné en argument

	// Tenter de changer de répertoire avec chdir()
	// - Si chdir échoue, afficher une erreur (répertoire inexistant, permissions, etc.)

	// Si changement réussi :
	// - Mettre à jour $PWD avec le nouveau répertoire (getcwd())
	// - Mettre à jour $OLDPWD dans **envp
}