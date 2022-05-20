#include "philosophers.h"

unsigned long   get_current_time(void)
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

unsigned long   get_time(unsigned long start)
{
    return (get_current_time() - start);
}

void    ft_print(char *str, t_philo *ph)
{
    pthread_mutex_lock(&(ph->pinfo->print));
    printf("%ld %d %s", get_time(ph->pinfo->start), ph->ph_id + 1, str);
    pthread_mutex_unlock(&(ph->pinfo->print));
}

void	ft_usleep(unsigned long date)
{
	unsigned long	us;

	us = get_current_time();
	while (get_current_time() - us < date)
		usleep(50);
}

static int	is_w_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft1_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	if (!str)
		return (-1);
	res = 0;
	i = 0;
	while (is_w_space(str[i]))
		i++;
	sign = 1 - (str[i] == '-') * 2;
	i += (str[i] == '+' || str[i] == '-');
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (sign * res);
}