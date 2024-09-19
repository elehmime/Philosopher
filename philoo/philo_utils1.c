/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:11:15 by ellehmim          #+#    #+#             */
/*   Updated: 2024/09/19 22:45:02 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_time()
{
	struct timeval	tv;
	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_time(size_t set_time, int id, char *str, t_philo_data *philo_data)
{
	long	time;

	time = get_time() - set_time;
	pthread_mutex_lock(&philo_data->philo->death_mutex);
	pthread_mutex_lock(&philo_data->philo->print_msg);
	if (philo_data->philo->dead == 0)
	{
		printf("%ld %d %s\n", time, id, str);
	}	
	pthread_mutex_unlock(&philo_data->philo->print_msg);
	pthread_mutex_unlock(&philo_data->philo->death_mutex);
}

int	philo_eating(t_philo_data	*philo_data)
{
	if (philo_is_dead(philo_data))
	{
		drop_forks(philo_data);
		return (1);
	}
	pthread_mutex_lock(&philo_data->philo->meal);
	print_time(philo_data->philo->set_time, philo_data->id, "is eating", philo_data);
	philo_data->last_meal_time = get_time();
	philo_data->nb_of_eaten++;
	pthread_mutex_unlock(&philo_data->philo->meal);
	ft_sleep(philo_data, philo_data->philo->time_to_eat);
	drop_forks(philo_data);
	if (philo_data->nb_of_eaten == philo_data->philo->nb_eat)
		return (1);
	if (philo_is_dead(philo_data))
		return (1);
	return (0);
}

int	philo_sleep(t_philo_data *philo_data)
{
	if (philo_is_dead(philo_data))
		return (1);
	print_time(philo_data->philo->set_time, philo_data->id, "is sleeping", philo_data);
	ft_sleep(philo_data, philo_data->philo->time_to_sleep);
	if (philo_is_dead(philo_data))
		return (1);
	return (0);
}

int    philo_thinking(t_philo_data *philo_data)
{
    if (philo_is_dead(philo_data))
        return (1);
    print_time(philo_data->philo->set_time, philo_data->id, "is thinking", philo_data);;
    ft_sleep(philo_data, (philo_data->philo->time_to_die - (philo_data->philo->time_to_eat + philo_data->philo->time_to_sleep)) / 2);
    return (0);
}

// int	philo_thinking(t_philo_data *philo_data)
// {
// 	if (philo_is_dead(philo_data))
// 		return (1);
// 	print_time(philo_data->philo->set_time, philo_data->id, "is thinking", philo_data);
// 	while(philo_data->philo->time_to_die - (get_time() - philo_data->last_meal_time) > philo_data->philo->time_to_eat)
// 	{
// 		pthread_mutex_lock(&philo_data->philo->death_mutex);
// 		if (philo_data->philo->dead == 1)
// 		{
// 			pthread_mutex_unlock(&philo_data->philo->death_mutex);
// 			return (1);
// 		}
// 		pthread_mutex_unlock(&philo_data->philo->death_mutex);
// 		usleep(1000);
// 	}
// 	return (0);
// }
