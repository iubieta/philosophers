/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:30 by iubieta-          #+#    #+#             */
/*   Updated: 2024/11/02 14:24:39 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	size_t	id;
	int		status; // 1:Thinking, 2:Eating, 3:Sleeping, 0:Dead.
	size_t	t_die;
	size_t	t_eat;
	size_t	t_sleep;
	size_t	last_meal;
	size_t	n_meals;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *death_lock;
	pthread_mutex_t *write_lock;
}	t_philo;

typedef struct s_mutex_group
{
	pthread_mutex_t death_lock;
	pthread_mutex_t write_lock;
	pthread_mutex_t *forks;
}	t_mutex_group;

// MUTEX
int		init_all_mutex(t_mutex_group *mutex_group, size_t *args);
int		init_mutex(pthread_mutex_t *mutex);
int		init_forks(pthread_mutex_t **forks, size_t n);
void 	*lock_mutex(pthread_mutex_t *mutex);
void 	*unlock_mutex(pthread_mutex_t *mutex);

// PHILOS
int 	init_philos(t_philo **table, t_mutex_group *mutex_group, size_t *args);
void	fill_philo_data(t_philo *philo, size_t i, size_t *args, t_mutex_group *mutex_group);
void	print_philo_data(t_philo philo);
void	send_message(char *str, t_philo *philo);

// ROUTINES
pthread_t	*start_routines(size_t *args, t_philo *philo);
void		*monitor_routine(void *arg);
void		*philo_routine(void *arg);
void		eat(t_philo *philo);
void		send_message(char *str, t_philo *philo);

// UTILS
int		ft_atoi(const char *s);
size_t	ft_atosizet(const char *s);
int		printe(char *str);
int		prints(char *str);

#endif
