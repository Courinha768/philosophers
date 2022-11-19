#include "../includes/philosophers.h"

int	write_error(int type)
{
	if (type == 1)
		my_putstr("Incorrect number of arguments\n", 2);
	if (type == 2)
		my_putstr("All arguments should be numbers\n", 2);
	return (1);
}

int	check_args_isdigit(int ac, char **av)
{
	int	i;

	ac -= 1;
	while (ac > 0)
	{
		i = -1;
		while (av[ac][++i])
			if (av[ac][i] < 48 || av[ac][i] > 57)
				return (1);
		ac--;
	}
	return (0);
}

int	error_handler(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (write_error(1));
	if (check_args_isdigit(ac, av))
		return (write_error(2));
	return (0);
}
