#include "philosophers.h"

int is_digit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            return (1);
        i++;
    }
    return (0);
}

int check_args(int ac, char **av)
{
    int i;

    i = 1;
    if (ac < 5 || ac > 6)
        return (0);
    while (i < ac)
    {
        if (!is_digit(av[i]))
            return (0);
        if ((ft1_atoi(av[i])) <= 0)
            return (0);
        if ((ft1_atoi(av[i])) > 2147483647)
            return (0);
        i++;
    }
    return (1);
}