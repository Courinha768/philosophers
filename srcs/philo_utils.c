#include "../includes/philosophers.h"

void	my_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	my_atoi(char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 10 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == 45)
		sign = -1;
	if (str[i] == 45 || str[i] == 43)
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (sign * result);
}

void	define_args(t_args *args, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		args->nbr_of_philo = my_atoi(av[1]);
		args->time_to_die = my_atoi(av[2]);
		args->time_to_eat = my_atoi(av[3]);
		args->time_to_sleep = my_atoi(av[4]);
		if (ac == 6)
			args->eat_amount = my_atoi(av[5]);
	}
}
