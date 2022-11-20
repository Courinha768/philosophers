#include "../includes/philosophers.h"

void	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	putmsg(1, *philo);
	pthread_mutex_lock(philo->rght_fork);
	putmsg(1, *philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (!philo->finish)
		putmsg(2, *philo);
	usleep(philo->args.time_to_eat * 1000);
	pthread_mutex_unlock(philo->rght_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->mutex);
}

void	sleeping(t_philo *philo)
{
	putmsg(3, *philo);
	usleep(philo->args.time_to_sleep * 1000);
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
		usleep(philo.args.time_to_eat * 1000);
	while (!philo.finish)
	{
		pickup_forks(&philo);
		eat(&philo);
		sleeping(&philo);
		thinking(&philo);
	}
	return (NULL);
}