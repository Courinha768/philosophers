/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aappleto <aappleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:55:08 by aappleto          #+#    #+#             */
/*   Updated: 2022/11/27 19:58:09 by aappleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	pickup_forks(t_philo *philo)
{
	if (!(philo->index % 2))
	{
		pthread_mutex_lock(philo->left_fork);
		putmsg(1, *philo);
		pthread_mutex_lock(philo->rght_fork);
		putmsg(1, *philo);
	}
	else
	{
		pthread_mutex_lock(philo->rght_fork);
		putmsg(1, *philo);
		pthread_mutex_lock(philo->left_fork);
		putmsg(1, *philo);
	}
}

void	eat(t_philo *philo)
{
	static long unsigned int	last_meal;

	if (last_meal)
		if ((int)(my_gettimeofday() - last_meal) > philo->args.time_to_die)
			philo->finish = 1;
	last_meal = my_gettimeofday();
	if (!philo->finish)
		putmsg(2, *philo);
	my_usleep(philo->args.time_to_eat);
	pthread_mutex_unlock(philo->rght_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	putmsg(3, *philo);
	my_usleep(philo->args.time_to_sleep);
}

void	thinking(t_philo *philo)
{
	putmsg(4, *philo);
}

void	*routine(void *philo_void)
{
	t_philo			philo;

	philo = *(t_philo *)philo_void;
	if (!(philo.index % 2))
		my_usleep(10);
	while (!philo.finish && philo.args.eat_amount--)
	{
		pickup_forks(&philo);
		eat(&philo);
		sleeping(&philo);
		thinking(&philo);
	}
	if (philo.finish)
	{
		putmsg(5, philo);
		exit(1);
	}
	return (NULL);
}
