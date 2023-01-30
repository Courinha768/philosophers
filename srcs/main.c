/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:54:57 by aappleto          #+#    #+#             */
/*   Updated: 2022/12/04 18:02:45 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	putmsg(2, *philo);
	philo->last_meal = my_gettimeofday();
	if (philo->args.time_to_eat > philo->args.time_to_die)
	{
		my_usleep(philo->args.time_to_die);
		philo->finish = 1;
	}
	else
	{
		my_usleep(philo->args.time_to_eat);
		pthread_mutex_unlock(philo->rght_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
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
		else
			args->eat_amount = -1;
	}
}

int	main(int ac, char **av)
{
	t_args		args;

	if (error_handler(ac, av))
		return (0);
	define_args(&args, ac, av);
	smutex();
	run_philosophers(args);
	return (0);
}
