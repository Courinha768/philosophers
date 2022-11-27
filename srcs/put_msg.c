/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aappleto <aappleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:55:05 by aappleto          #+#    #+#             */
/*   Updated: 2022/11/27 21:04:33 by aappleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	putmsg(int type, t_philo philo)
{
	pthread_mutex_lock(smutex());
	printf("%-7ld %d", my_gettimeofday() - stime(), philo.index);
	if (type == 1)
		printf(" has taken a fork\n");
	if (type == 2)
		printf(" is eating\n");
	if (type == 3)
		printf(" is sleeping\n");
	if (type == 4)
		printf(" is thinking\n");
	if (type == 5)
		printf(" died\n");
	pthread_mutex_unlock(smutex());
}
