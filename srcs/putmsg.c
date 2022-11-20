#include "../includes/philosophers.h"

void	my_putnbr(int n)
{
	if (n < 10)
	{
		n = n + 48;
		write(1, &n, 1);
	}
	else
	{
		my_putnbr(n / 10);
		n = n % 10 + 48;
		write(1, &n, 1);
	}
}

void	putmsg(int type, t_philo philo)
{
	struct timeval	tv;
	int				time;
	int				tstart;

	tstart = stime();
	gettimeofday(&tv, NULL);
	time = tv.tv_usec - tstart;
	my_putnbr(time);
	(void)tstart;
	write(1, " ", 1);
	my_putnbr(philo.index);
	if (type == 1)
		my_putstr(" has taken a fork\n", 1);
	if (type == 2)
		my_putstr(" is eating\n", 1);
	if (type == 3)
		my_putstr(" is sleeping\n", 1);
	if (type == 4)
		my_putstr(" is thinking\n", 1);
	if (type == 5)
		my_putstr(" died\n", 1);
}
