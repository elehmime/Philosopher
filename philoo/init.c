/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:54:35 by ellehmim          #+#    #+#             */
/*   Updated: 2024/09/17 15:39:40 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    info_struct(char **av, t_philo *philo)
{
    philo->nb_philo = ft_atoi_strict(av[1]);
    philo->time_to_die = ft_atoi_strict(av[2]);
    philo->time_to_eat = ft_atoi_strict(av[3]);
    philo->time_to_sleep = ft_atoi_strict(av[4]);
	philo->nb_eat = -1;
	philo->dead = 0;
	if (av[5])
        philo->nb_eat = ft_atoi_strict(av[5]);
}

int	init_mutex(t_philo *philo)
{
	if (pthread_mutex_init(&philo->death_mutex, NULL))
		return (printf("Error mutex init death\n"), 1);
	if (pthread_mutex_init(&philo->print_msg, NULL))
		return (printf("Error mutex init print\n"), 1);
	if (pthread_mutex_init(&philo->sleeping, NULL))
		return (printf("Error mutex init sleeping\n"), 1);
	if (pthread_mutex_init(&philo->meal, NULL))
		return (printf("Error mutex init meal\n"), 1);
	return (0);
}

int init_philo(t_philo *philo)
{
	int i;

	i = 0;
	philo->philo_data = malloc(sizeof(t_philo_data) * philo->nb_philo);/* A verifier*/
	if (!philo->philo_data)
		return (0);
	while (i < philo->nb_philo)
	{
		philo->philo_data[i].philo = philo;
		philo->philo_data[i].id = i + 1;
		philo->philo_data[i].nb_of_eaten = 0;
		philo->philo_data[i].last_meal_time = 0;
		if (pthread_mutex_init(&philo->philo_data[i].r_forks, NULL))
			return (printf("Error mutex init fork\n"), 1);
		if (i == 0)
			philo->philo_data[i].l_fork = &philo->philo_data[philo->nb_philo - 1].r_forks;
		else
			philo->philo_data[i].l_fork = &philo->philo_data[i - 1].r_forks;
		i++;
	}
	return (0);
}
