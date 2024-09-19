/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:20:21 by ellehmim          #+#    #+#             */
/*   Updated: 2024/09/19 00:06:04 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    last_eat(t_philo_data *philo_data)
{
    pthread_mutex_lock(&philo_data->philo->meal);
    philo_data->last_meal_time = get_time();
    pthread_mutex_unlock(&philo_data->philo->meal);
}

int take_odd_fork(t_philo_data *philo_data)
{
	pthread_mutex_lock(philo_data->l_fork);
	if (philo_is_dead(philo_data))
	{
		pthread_mutex_unlock(philo_data->l_fork);
		return (1);
	}
	print_time(philo_data->philo->set_time, philo_data->id, "has taken a fork", philo_data);
	pthread_mutex_lock(&philo_data->r_forks);
		if (philo_is_dead(philo_data))
		{
			pthread_mutex_unlock(philo_data->l_fork);
			pthread_mutex_unlock(&philo_data->r_forks);
			return (1);
		}
	print_time(philo_data->philo->set_time, philo_data->id, "has taken a fork", philo_data);
	return (0);
}

int take_a_fork(t_philo_data *philo_data)
{
	if(philo_data->id % 2 == 1)
		usleep(100);
	if (philo_data->id % 2 == 0)
	{
		pthread_mutex_lock(&philo_data->r_forks);
		if (philo_is_dead(philo_data))
		{
			pthread_mutex_unlock(&philo_data->r_forks);
			return (1);
		}
		print_time(philo_data->philo->set_time, philo_data->id, "has taken a fork", philo_data);
		pthread_mutex_lock(philo_data->l_fork);
		if (philo_is_dead(philo_data))
		{
			pthread_mutex_unlock(&philo_data->r_forks);
			pthread_mutex_unlock(philo_data->l_fork);
			return (1);
		}
		print_time(philo_data->philo->set_time, philo_data->id, "has taken a fork", philo_data);
	}
	else
		if (take_odd_fork(philo_data))
			return (1);
	return (0);
}
int	drop_forks(t_philo_data *philo_data)
{
	if (philo_data->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo_data->r_forks);
		pthread_mutex_unlock(philo_data->l_fork);	
	}
	else
	{
		pthread_mutex_unlock(&philo_data->r_forks);
		pthread_mutex_unlock(philo_data->l_fork);
	}
	return (0);
}

void	*philo_routine(void *data)
{
	t_philo_data	*philo_data;
	
	philo_data = (t_philo_data *)data;
    last_eat(philo_data);
	// if(philo_data->id % 2 == 1)
	// 	usleep(100);
    while (1)
    {
        if (take_a_fork(philo_data))
			break;
		if (philo_is_dead(philo_data))
			break;
		if (philo_eating(philo_data))
			break;
		if (philo_is_dead(philo_data))
			break;
		if (philo_sleep(philo_data))
			break;
		if (philo_is_dead(philo_data))
			break;
		if (philo_thinking(philo_data))
			break;
    }
	return (NULL);
}
