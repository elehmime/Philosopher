/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:45:59 by ellehmim          #+#    #+#             */
/*   Updated: 2024/09/17 14:39:16 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_atoi_strict(char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb);
}

int parsing(int ac, char **av)
{
	int	i;

	i = 1;
    if (ac < 5 || ac > 6)
        return (1);
    if (!av)
        return (1);
    while (i < 5)
	{
		if (!ft_atoi_strict(av[i]) || ft_atoi_strict(av[i]) > INT_MAX)
			return (1);
		if (i > 1)
			if (ft_atoi_strict(av[i]) < 60)
				return (2);
		i++;
	}
	if (av[5])
		if (!ft_atoi_strict(av[5]) || ft_atoi_strict(av[5]) > INT_MAX)
			return (3);
	return (0);
}
