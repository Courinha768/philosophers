/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:06:04 by fmeira            #+#    #+#             */
/*   Updated: 2022/12/04 17:41:12 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args {
	int	nbr_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_amount;
}	t_args;

typedef struct s_philo {
	pthread_t			th;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*rght_fork;
	pthread_mutex_t		*mutex;
	t_args				args;
	int					index;
	int					finish;
	long unsigned int	last_meal;
}	t_philo;

typedef struct s_info {
	t_philo			*philo;
	t_args			args;
	struct timeval	tstart;
	int				index;
}	t_info;

/* ========================================================================== */
/*                                   MAIN                                     */
/* ========================================================================== */

void				define_args(t_args *args, int ac, char **av);

/* ========================================================================== */
/*                              PHILOSOPHERS.C                                */
/* ========================================================================== */

void				run_philosophers(t_args args);
t_philo				*create_forks(t_philo *philo, t_args args);
t_philo				*init_philosophers(t_args args);

/* ========================================================================== */
/*                                 ROUTINE                                    */
/* ========================================================================== */

void				pickup_forks(t_philo *philo, int i);
void				eat(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				*routine(void *philo_void);

/* ========================================================================== */
/*                                  UTILS                                     */
/* ========================================================================== */

long unsigned int	my_gettimeofday(void);
void				my_usleep(int time);
int					my_atoi(char *str);
void				my_putstr(char *str, int fd);
long unsigned int	stime(void);
pthread_mutex_t		*smutex(void);

/* ========================================================================== */
/*                                  ERROR                                     */
/* ========================================================================== */

int					error_handler(int ac, char **av);
int					write_error(int type);
int					check_args_isdigit(int ac, char **av);

/* ========================================================================== */
/*                                   MSGS                                     */
/* ========================================================================== */

void				putmsg(int type, t_philo philo);
void				my_putnbr(int n);

#endif
