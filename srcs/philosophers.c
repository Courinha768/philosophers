#include "../includes/philosophers.h"

void	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	putmsg(1, *philo, 100000);
	pthread_mutex_lock(philo->rght_fork);
	putmsg(1, *philo, 100000);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (!philo->finish)
		putmsg(2, *philo, 10000);
	usleep(philo->args.time_to_eat);
	pthread_mutex_unlock(philo->rght_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->mutex);
}

void	sleeping(t_philo *philo)
{
	putmsg(3, *philo, 100000);
	usleep(philo->args.time_to_sleep);
}

void	thinking(t_philo *philo)
{
	putmsg(4, *philo, 100000);
}

void	*routine(void *philo_void)
{
	t_philo			philo;

	philo = *(t_philo *)philo_void;
	if (!(philo.index % 2))
		usleep(philo.args.time_to_eat);
	while (!philo.finish)
	{
		pickup_forks(&philo);
		eat(&philo);
		sleeping(&philo);
		thinking(&philo);
	}
	return (NULL);
}

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
	int		i;
	t_philo	*philo;

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
