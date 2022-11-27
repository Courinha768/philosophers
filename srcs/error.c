/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aappleto <aappleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:54:49 by aappleto          #+#    #+#             */
/*   Updated: 2022/11/27 19:55:38 by aappleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	write_error(int type)
{
	if (type == 1)
		write(2, "Incorrect number of arguments\n", 31);
	if (type == 2)
		write(2, "All arguments should be numbers\n", 33);
	return (1);
}

int	check_args_isdigit(int ac, char **av)
{
	int	i;

	ac -= 1;
	while (ac > 0)
	{
		i = -1;
		while (av[ac][++i])
			if (av[ac][i] < 48 || av[ac][i] > 57)
				return (1);
		ac--;
	}
	return (0);
}

int	error_handler(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (write_error(1));
	if (check_args_isdigit(ac, av))
		return (write_error(2));
	return (0);
}
