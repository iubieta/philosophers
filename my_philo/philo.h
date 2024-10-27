/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:30 by iubieta-          #+#    #+#             */
/*   Updated: 2024/10/27 20:14:12 by iubieta-         ###   ########.fr       */
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
	int status; // 1:Despierto, 2:Comiendo, 3:Durmiendo, 0:muerto
	size_t	t_die;
	size_t t_eat;
	size_t t_sleep;
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

//MEMORY
int		init_all_mutex(t_mutex_group *mutex_group, size_t *args);
int		init_philos(t_philo **table, t_mutex_group mutex_group, size_t *args);
void	*lock_mutex(pthread_mutex_t *mutex);

//UTILS
int		ft_atoi(const char *s);
size_t	ft_atosizet(const char *s);
int		printe(char *str);
int		prints(char *str);



//MAIN FUNCTIONS
pthread_t	*start_routines(size_t *args, t_philo **philo/*, t_mutex_group *mutex_group*/);

#endif
