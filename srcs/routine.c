/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:55:08 by aappleto          #+#    #+#             */
/*   Updated: 2022/12/04 18:03:05 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	agora_fica_certo(t_philo *philo)
{
	philo->last_meal = my_gettimeofday();
	if (!philo->finish)
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
}

void	pickup_forks(t_philo *philo, int i)
{
	if ((int)(my_gettimeofday() - philo->last_meal) > philo->args.time_to_die)
		philo->finish = 1;
	if (i == 1)
	{
		if (philo->args.time_to_die < 2 * philo ->args.time_to_eat)
		{
			my_usleep(philo->args.time_to_die - \
			philo->args.time_to_eat - philo->args.time_to_sleep);
			philo->finish = 1;
		}
	}
	else
	{
		agora_fica_certo(philo);
	}
}

void	sleeping(t_philo *philo)
{
	if ((int)(my_gettimeofday() - philo->last_meal) > philo->args.time_to_die)
		philo->finish = 1;
	if ((int)(my_gettimeofday() - philo->last_meal) + philo->args.time_to_sleep \
	> philo->args.time_to_die)
	{
		my_usleep(philo->args.time_to_die - philo->args.time_to_eat);
		philo->finish = 1;
	}
	else
	{
		putmsg(3, *philo);
		my_usleep(philo->args.time_to_sleep);
	}
}

void	thinking(t_philo *philo)
{
	if (!philo->finish)
		putmsg(4, *philo);
}

void	*routine(void *philo_void)
{
	t_philo			philo;
	int				i;

	i = 0;
	philo = *(t_philo *)philo_void;
	if (philo.index % 2)
		my_usleep(philo.args.time_to_eat);
	while (!philo.finish && philo.args.eat_amount--)
	{
		pickup_forks(&philo, i);
		if (!philo.finish)
		{
			eat(&philo);
			sleeping(&philo);
			thinking(&philo);
		}
		i++;
	}
	if (philo.finish)
	{
		putmsg(5, philo);
		exit(1);
	}
	return (NULL);
}
