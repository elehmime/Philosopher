/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellehmim <ellehmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 08:48:52 by ellehmim          #+#    #+#             */
/*   Updated: 2024/09/17 15:33:56 by ellehmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_data
{
	int				id;
	int				nb_of_eaten;
	int				last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	r_forks;
	pthread_mutex_t	*l_fork;
	struct s_philo	*philo;
}					t_philo_data;

typedef struct s_philo
{
	int				nb_philo;
	int				nb_eat;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				dead;
	size_t			set_time;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_msg;
	pthread_mutex_t	meal;
	pthread_mutex_t	sleeping;
	t_philo_data	*philo_data;
}					t_philo;

/*main*/
void		*one_philo_routine(void *phil);
void		creat_thread_one_philo(t_philo *philo);
void		print_time_one(size_t set_time, int id, char *str);
void		free_all(t_philo *philo);

/*Parsing.c*/
int			parsing(int ac, char **av);
long		ft_atoi_strict(char *str);

/*init.c*/
int			init_mutex(t_philo *philo);
int			init_philo(t_philo *philo);
void		info_struct(char **av, t_philo *philo);

/*philo.c*/
int			philosophers(char **av, t_philo *philo);
int			creat_thread_philo(t_philo *philo);
int			check_dead(t_philo_data *philo_data);
int			philo_is_dead(t_philo_data *philo_data);
int			ft_sleep(t_philo_data *philo_data, int time);

/*philo_utils*/
int			take_a_fork(t_philo_data *philo_data);
int			drop_forks(t_philo_data *philo_data);
int			take_odd_fork(t_philo_data *philo_data);
void		*philo_routine(void *data);
void		last_eat(t_philo_data *philo_data);

/*philo_utils1.c*/
int			philo_eating(t_philo_data	*philo_data);
int			philo_sleep(t_philo_data *philo_data);
int			philo_thinking(t_philo_data *philo_data);
int			get_time();
void		print_time(size_t set_time, int id, char *str, t_philo_data *philo_data);


#endif