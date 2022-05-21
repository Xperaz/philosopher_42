/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:54:35 by aouhadou          #+#    #+#             */
/*   Updated: 2022/05/20 13:01:56 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct info
{
	int				n;
	useconds_t		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max;
	int				all_eat;
	unsigned long	start;
	pthread_mutex_t	print;
}					t_info;

typedef struct philos
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		philo;
	int				ph_id;
	t_info			*pinfo;
	int				meals;
	unsigned long	last_meal;
}					t_philo;

//check errors
int				is_digit(char *str);
int				check_args(int ac, char **av);
//parsing
int				ft_atoi(const char *str);
unsigned long	get_current_time(void);
unsigned long	get_time(unsigned long start);
void			ft_print(char *str, t_philo *ph);
void			ft_usleep(unsigned long time);

#endif
