#include "../includes/philosophers.h"

t_philo	*create_forks(t_philo *philo, t_args args)
{
	int				i;
	int				size;
	pthread_mutex_t	*forks;

	i = 0;
	size = sizeof(pthread_mutex_t) * args.nbr_of_philo;
	forks = (pthread_mutex_t *)malloc(size);
	if (!forks)
		return (NULL);
	while (i < 3)
	{
		pthread_mutex_init(&forks[i], NULL);
		pthread_mutex_init(&(philo[i].mutex), NULL);
		if (i == 0)
			philo[i].left_fork = &forks[args.nbr_of_philo - 1];
		else
			philo[i].left_fork = &forks[i - 1];
		philo[i].rght_fork = &forks[i];
		i++;
	}
	free(forks);
	return (philo);
}

t_philo	*init_philo(t_args args)
{
	int				i;
	t_philo			*philo;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * args.nbr_of_philo);
	if (!philo)
		return (NULL);
	while (++i < args.nbr_of_philo)
	{
		philo[i].index = i + 1;
		philo[i].args = args;
		philo[i].finish = 0;
	}
	philo = create_forks(philo, args);
	return (philo);
}

void	run_philo(t_args args)
{
	t_philo	*philo;
	int		i;
	int		outp;

	philo = init_philo(args);
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

int	main(int ac, char **av)
{
	t_args		args;

	if (error_handler(ac, av))
		return (0);
	define_args(&args, ac, av);
	run_philo(args);
	return (0);
}
