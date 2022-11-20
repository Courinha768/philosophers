#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_args {
	int	nbr_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_amount;
}	t_args;

typedef struct	s_philo {
	pthread_t		th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*rght_fork;
	pthread_mutex_t	mutex;
	t_args			args;
	int				index;
	int				finish;
}	t_philo;

typedef struct	s_info {
	t_philo			*philo;
	t_args			args;
	struct timeval	tstart;
	int				index;
}	t_info;

/* ========================================================================== */
/*                              PHILOSOPHERS.C                                */
/* ========================================================================== */

t_philo	*create_forks(t_philo *philo, t_args args);

/* ========================================================================== */
/*                                  UTILS                                     */
/* ========================================================================== */

int		my_atoi(char *str);
void	define_args(t_args *args, int ac, char **av);
void	my_putstr(char *str, int fd);

/* ========================================================================== */
/*                                  ERROS                                     */
/* ========================================================================== */

int		error_handler(int ac, char **av);
int		write_error(int	type);
int		check_args_isdigit(int ac, char **av);

/* ========================================================================== */
/*                                   MSGS                                     */
/* ========================================================================== */

void	putmsg(int	type, t_philo philo, long int tstart);
void	my_putnbr(int n);

#endif