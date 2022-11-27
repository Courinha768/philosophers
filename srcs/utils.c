/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aappleto <aappleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:55:10 by aappleto          #+#    #+#             */
/*   Updated: 2022/11/27 19:56:33 by aappleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long unsigned int	my_gettimeofday(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

void	my_usleep(int time)
{
	long unsigned int	a;

	a = my_gettimeofday() + time;
	while (my_gettimeofday() < a)
		a = a;
}

int	my_atoi(char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 10 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == 45)
		sign = -1;
	if (str[i] == 45 || str[i] == 43)
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (sign * result);
}

long unsigned int	stime(void)
{
	static long unsigned int	stime;

	if (!stime)
	{
		stime = my_gettimeofday();
	}
	return (stime);
}
