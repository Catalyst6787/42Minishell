/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:15:22 by kgiraud           #+#    #+#             */
/*   Updated: 2025/02/05 16:14:33 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

pid_t	fgv_last_pid(pid_t new)
{
	static pid_t	pid;
	
	if (new == -1)
		return (pid);
	pid = new;
	return (pid);
}
