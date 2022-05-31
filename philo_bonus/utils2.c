/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:57:00 by aouhadou          #+#    #+#             */
/*   Updated: 2022/05/26 13:57:47 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	killall(int *pids, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		kill(pids[i], SIGKILL);
}

int	waitpids(t_info pinfo, int childs)
{
	int	status;

	if (!childs)
		return (EXIT_SUCCESS);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		return (waitpids(pinfo, childs - 1));
	return (killall(pinfo.pid, pinfo.n), EXIT_FAILURE);
}
