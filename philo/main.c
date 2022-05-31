/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:29:05 by aouhadou          #+#    #+#             */
/*   Updated: 2022/05/20 12:45:04 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	if (ph->ph_id % 2)
		ft_usleep(ph->pinfo->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(ph->right_fork);
		ft_print("taken right fork\n", ph);
		pthread_mutex_lock(ph->left_fork);
		ft_print("taken left fork\n", ph);
		ft_print("is eating\n", ph);
		ph->last_meal = get_time(ph->pinfo->start);
		ft_usleep(ph->pinfo->time_to_eat);
		(ph->meals)++;
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		if (ph->meals >= ph->pinfo->max && ph->pinfo->max != -1)
			return ((ph->pinfo->all_eat)++, ptr);
		ft_print("is sleeping\n", ph);
		ft_usleep(ph->pinfo->time_to_sleep);
		ft_print("is thinking\n", ph);
	}
	return (ptr);
}

void	ft_check(t_info *info, t_philo *ph)
{
	int	i;

	while (1)
	{
		if (info->all_eat == info->n)
			return ;
		i = -1;
		while (++i < info->n)
		{
			if (ph[i].meals >= info->max && info->max != -1)
				continue ;
			if (get_time(info->start) - ph[i].last_meal >= info->time_to_die)
			{
				pthread_mutex_lock(&(info->print));
				printf("%ld %d Dead\n", get_time(info->start), i + 1);
				return ;
			}
		}
		usleep(100);
	}
}

void	create_philo(t_info *pinfo, t_philo *ph, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < pinfo->n)
	{
		ph[i].pinfo = pinfo;
		ph[i].last_meal = 0;
		pthread_create(&(ph[i].philo), NULL, routine, &ph[i]);
		pthread_detach((ph[i].philo));
	}
	ft_check(pinfo, ph);
	usleep(100);
	while (i--)
		pthread_mutex_destroy(&forks[i]);
}

t_info	init(char **av, pthread_mutex_t **forks, t_philo **ph)
{
	t_info	pinfo;
	int		i;

	pinfo.n = ft_atoi(av[1]);
	pinfo.time_to_die = (useconds_t)ft_atoi(av[2]);
	pinfo.time_to_eat = (useconds_t)ft_atoi(av[3]);
	pinfo.time_to_sleep = (useconds_t)ft_atoi(av[4]);
	pinfo.max = ft_atoi(av[5]);
	*forks = (pthread_mutex_t *)malloc(pinfo.n * sizeof(pthread_mutex_t));
	*ph = (t_philo *)malloc(pinfo.n * sizeof(t_philo));
	if (!*forks || !*ph)
		return (pinfo);
	pthread_mutex_init(&(pinfo.print), NULL);
	i = -1;
	while (++i < pinfo.n)
	{
		pthread_mutex_init(*forks + i, NULL);
		(*ph)[i].meals = 0;
		(*ph)[i].right_fork = *forks + i;
		(*ph)[i].left_fork = (*forks) + (i + 1) % pinfo.n;
		(*ph)[i].ph_id = i;
	}
	return (pinfo);
}

int	main(int ac, char **av)
{
	t_info			pinfo;
	t_philo			*ph;
	pthread_mutex_t	*forks;

	if (!check_args(ac, av))
	{
		printf("Error\n");
		return (0);
	}
	pinfo = init(av, &forks, &ph);
	if (!forks || !ph)
		return (free(forks), free(ph), 0);
	pinfo.start = get_current_time();
	create_philo(&pinfo, ph, forks);
	pthread_mutex_destroy(&(pinfo.print));
	free(ph);
	free(forks);
	return (0);
}
