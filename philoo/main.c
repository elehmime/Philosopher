/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 08:45:22 by ellehmim          #+#    #+#             */
/*   Updated: 2024/09/17 15:29:54 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_time_one(size_t set_time, int id, char *str)
{
	long	time;

	time = get_time() - set_time;
	printf("%ld %d %s\n", time, id, str);
}

void	free_all(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_destroy(&philo->philo_data[i].r_forks);
		i++;
	}
	pthread_mutex_destroy(&philo->death_mutex);
	pthread_mutex_destroy(&philo->print_msg);
	pthread_mutex_destroy(&philo->meal);
	pthread_mutex_destroy(&philo->sleeping);
	free(philo->philo_data);
}

void	creat_thread_one_philo(t_philo *philo)
{
	pthread_create(&philo->philo_data[0].thread, NULL, one_philo_routine,
	&philo[0]);
	pthread_join(philo->philo_data[0].thread, NULL);
}

void	*one_philo_routine(void *phil)
{
	t_philo	*philo;
	
	philo = (t_philo *)phil;
    pthread_mutex_lock(&philo->philo_data->r_forks);
    pthread_mutex_lock(&philo->print_msg);
	print_time_one(philo->set_time, philo->philo_data[0].id, "has taken a fork");
    pthread_mutex_unlock(&philo->print_msg);
    usleep(philo->time_to_die * 1000);
    pthread_mutex_unlock(&philo->philo_data->r_forks);
    pthread_mutex_lock(&philo->print_msg);
	print_time_one(philo->set_time, philo->philo_data[0].id, "died");
    pthread_mutex_unlock(&philo->print_msg);
    return (NULL);
}

int main(int ac, char **av)
{
    t_philo philo;
    if (parsing(ac, av))
    {
        printf("Error params\n");
        return (0);
    }
	if (philosophers(av, &philo))
    {
        printf("Error init mutex\n");
        return (0);
    }
	free_all(&philo);
    return (0);
}
