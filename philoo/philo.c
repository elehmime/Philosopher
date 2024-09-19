/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:49:19 by ellehmim          #+#    #+#             */
/*   Updated: 2024/09/19 22:45:08 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo_data *philo_data, int time)
{
    long start_time;
    long current_time;
	
	if (time < 0)
		time = 0;
    start_time = get_time(); // Capture le temps de début
    while (1)
    {
        current_time = get_time(); // Capture le temps actuel

        if (philo_is_dead(philo_data)) // Vérifie si le philosophe est mort
            return (1);
        
        if ((current_time - start_time) >= time) // Si le temps écoulé dépasse le temps requis
            break;

        usleep(1000); // Pause de 1 ms pour ne pas trop surcharger la CPU
    }
    return (0);
	// int i;

	// i = 0;
	// while (i < time)
	// {
	// 	if (philo_is_dead(philo_data))
	// 		return (1);
	// 	usleep(1000);
	// 	i += 1;
	// }
	// if (philo_is_dead(philo_data))
	// 	return (1);
	// usleep((time % 10) * 1000);
	// return (0);
}

int	check_dead(t_philo_data *philo_data)
{
	int	time;
	int dead_line;

	time = get_time();
	dead_line = time - philo_data->last_meal_time;
	if (dead_line >= philo_data->philo->time_to_die)
	{
		pthread_mutex_lock(&philo_data->philo->death_mutex);
		pthread_mutex_lock(&philo_data->philo->print_msg);
		print_time_one(philo_data->philo->set_time, philo_data->id, "died");
		pthread_mutex_unlock(&philo_data->philo->print_msg);
		philo_data->philo->dead = 1;
		pthread_mutex_unlock(&philo_data->philo->death_mutex);
		return (1);
	}
	return (0);
}

int	philo_is_dead(t_philo_data *philo_data)
{
	pthread_mutex_lock(&philo_data->philo->death_mutex);
	if (philo_data->philo->dead == 1)
	{
		pthread_mutex_unlock(&philo_data->philo->death_mutex);	
		return (1);
	}
	pthread_mutex_unlock(&philo_data->philo->death_mutex);
	if (check_dead(philo_data))
		return (1);
	return (0);
}

int	creat_thread_philo(t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_create(&philo->philo_data[i].thread, NULL, &philo_routine, &philo->philo_data[i]))
			return (printf("Error thread creation\n"), 1);
		i++;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_join(philo->philo_data[i].thread, NULL);
		i++;
	}
	return (0);
}

int	philosophers(char **av, t_philo *philo)
{
	info_struct(av, philo);
	if (init_philo(philo))
		return (1);
	if (init_mutex(philo))
		return (1);
	philo->set_time = get_time();
	if (philo ->nb_philo == 1)
		creat_thread_one_philo(philo);
	else
		creat_thread_philo(philo);
	return (0);
	}
	