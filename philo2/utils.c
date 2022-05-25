/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:45:31 by aouhadou          #+#    #+#             */
/*   Updated: 2022/05/20 12:53:00 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

unsigned long	get_time(unsigned long start)
{
	return (get_current_time() - start);
}

void	ft_print(char *str, t_philo *ph)
{
	sem_wait((ph->pinfo->print));
	printf("%ld %d %s", get_time(ph->pinfo->start), ph->ph_id + 1, str);
	sem_post((ph->pinfo->print));
}

void	ft_usleep(unsigned long date)
{
	unsigned long	us;

	us = get_current_time();
	while (get_current_time() - us < date)
		usleep(10);
}
