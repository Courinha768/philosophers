/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aappleto <aappleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:55:00 by aappleto          #+#    #+#             */
/*   Updated: 2022/11/27 20:44:34 by aappleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philo	*create_forks(t_philo *philo, t_args args)
{
	int				i;
	int				size;
	pthread_mutex_t	*forks;

	size = sizeof(pthread_mutex_t) * args.nbr_of_philo;
	forks = (pthread_mutex_t *)malloc(size);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < args.nbr_of_philo)
		pthread_mutex_init(&forks[i], NULL);
	i = -1;
	while (++i < args.nbr_of_philo)
	{
		if (i == 0)
			philo[i].left_fork = &forks[args.nbr_of_philo - 1];
		else
			philo[i].left_fork = &forks[i - 1];
		philo[i].rght_fork = &forks[i];
	}
	free(forks);
	return (philo);
}

t_philo	*init_philosophers(t_args args)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)malloc(sizeof(t_philo) * args.nbr_of_philo);
	if (!p)
		return (NULL);
	i = -1;
	while (++i < args.nbr_of_philo)
	{
		p[i].index = i + 1;
		p[i].args = args;
		p[i].finish = 0;
	}
	p = create_forks(p, args);
	pthread_mutex_unlock(p[0].left_fork);
	pthread_mutex_unlock(p[1].left_fork);
	return (p);
}

void	run_philosophers(t_args args)
{
	t_philo	*philo;
	int		i;
	int		outp;

	philo = init_philosophers(args);
	stime();
	i = -1;
	outp = 0;
	while (++i < args.nbr_of_philo)
	{
		outp = pthread_create(&philo[i].th, NULL, routine, &philo[i]);
		if (outp)
			return ;
	}
	i = -1;
	while (++i < args.nbr_of_philo)
	{
		outp = pthread_join(philo[i].th, NULL);
		if (outp)
			return ;
	}
	free(philo);
}
