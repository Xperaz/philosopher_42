/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:51:46 by aouhadou          #+#    #+#             */
/*   Updated: 2022/05/26 13:54:33 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void	*ptr)
{
	t_philo	*ph;

	ph = (t_philo *)ptr;
	while (1)
	{
		sem_wait(ph->pinfo->fork);
		ft_print("take first fork\n", ph);
		sem_wait(ph->pinfo->fork);
		ft_print("take two forks\n", ph);
		ft_print("is eating\n", ph);
		ph->last_meal = get_current_time();
		ft_usleep(ph->pinfo->time_to_eat);
		(ph->meals)++;
		sem_post(ph->pinfo->fork);
		sem_post(ph->pinfo->fork);
		if (ph->meals >= ph->pinfo->max && ph->pinfo->max != -1)
			return (ptr);
		ft_print("is sleeping\n", ph);
		ft_usleep(ph->pinfo->time_to_sleep);
		ft_print("is thinking\n", ph);
	}
	return (ptr);
}

t_info	init(char **av)
{
	t_info	info;

	info.n = ft_atoi(av[1]);
	info.time_to_die = (useconds_t)ft_atoi(av[2]);
	info.time_to_eat = (useconds_t)ft_atoi(av[3]);
	info.time_to_sleep = (useconds_t)ft_atoi(av[4]);
	info.max = ft_atoi(av[5]);
	info.pid = (pid_t *)malloc(info.n * sizeof(pid_t));
	if (!info.pid)
		exit(1);
	sem_unlink("philo_printing");
	sem_unlink("philo_forks");
	info.print = sem_open("philo_printing", O_CREAT, S_IRWXU, 1);
	info.fork = sem_open("philo_forks", O_CREAT, S_IRWXU, info.n);
	if (info.print == SEM_FAILED || info.fork == SEM_FAILED)
	{
		if (info.fork == SEM_FAILED)
			sem_close(info.print);
		free(info.pid);
		exit(0);
	}
	info.start = get_current_time();
	return (info);
}

int	ft_check(t_info *info, t_philo *ph)
{
	while (1)
	{
		if (info->max != -1 && ph->meals >= info->max)
			return (EXIT_SUCCESS);
		if (get_current_time() - ph->last_meal > info->time_to_die)
		{
			sem_wait(ph->pinfo->print);
			printf("%ld %d dead\n", get_time(info->start) - 2, ph->ph_id + 1);
			return (EXIT_FAILURE);
		}
		usleep(500);
	}
}

void	init_process(int child, t_info info)
{
	t_philo		ph;
	pthread_t	philo;
	int			status;

	ph.ph_id = child;
	ph.last_meal = get_current_time();
	ph.meals = 0;
	ph.pinfo = &info;
	if (ph.ph_id % 2)
		ft_usleep(info.time_to_eat);
	pthread_create(&philo, NULL, routine, &ph);
	pthread_detach(philo);
	status = ft_check(&info, &ph);
	free(info.pid);
	exit(status);
}

int	main(int ac, char **av)
{
	t_info	info;
	int		i;
	int		status;

	if (!check_args(ac, av))
		return (printf("Error!\n"), 1);
	info = init(av);
	i = -1;
	while (++i < info.n)
	{
		info.pid[i] = fork();
		if (info.pid[i] == 0)
			init_process(i, info);
		else if (info.pid[i] == -1)
		{
			killall(info.pid, i);
			printf("Forks Not Created\n");
			exit(1);
		}
	}
	status = waitpids(info, info.n);
	free(info.pid);
	sem_close((info.print));
	sem_close((info.fork));
	exit(status);
}
