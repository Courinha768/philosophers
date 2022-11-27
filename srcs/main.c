/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aappleto <aappleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:54:57 by aappleto          #+#    #+#             */
/*   Updated: 2022/11/27 21:03:53 by aappleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
