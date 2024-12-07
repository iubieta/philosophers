/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta <iubieta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:30 by iubieta-          #+#    #+#             */
/*   Updated: 2024/12/07 16:29:53 by iubieta-         ###   ########.fr       */
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
	size_t			id;
	int				status;
	int				death_flag;
	size_t			start_t;
	size_t			n_philos;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			last_meal;
	size_t			n_meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*write_lock;
}	t_philo;

typedef struct s_mutex_group
{
	pthread_mutex_t	death_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
}	t_mutex_group;

typedef struct s_program
{
	size_t			*args;
	t_philo			*table;
	t_mutex_group	mutex_gr;
	pthread_t		*routines;
}	t_program;

// MUTEX
int			init_all_mutex(t_mutex_group *mutex_group, size_t *args);
int			init_mutex(pthread_mutex_t *mutex);
int			init_forks(pthread_mutex_t **forks, size_t n);
void		*lock_mutex(pthread_mutex_t *mutex);
void		*unlock_mutex(pthread_mutex_t *mutex);

// PHILOS
int			init_philos(t_philo **table, t_mutex_group *mutex_group,
				size_t *args);
void		fill_philo(t_philo *philo, size_t i, size_t *args,
				t_mutex_group *mutex_gr);
void		print_philo_data(t_philo philo);
void		send_message(char *str, t_philo *philo);
void		change_status(t_philo *philo, int status);

// ROUTINES
pthread_t	*start_routines(size_t *args, t_philo *philo);
void		*philo_routine(void *arg);
int			eat(t_philo *philo);
int			one_philo_exception(t_philo *philo);
void		send_message(char *str, t_philo *philo);

// MONITOR
void		*monitor_routine(void *arg);
int			dead_philo(t_philo *philo);
int			all_philos_finished(t_philo *philo);
void		force_philos_end(t_philo *philo);

// UTILS
int			ft_atoi(const char *s);
size_t		ft_atosizet(const char *s);
long		millis(void);
int			printe(char *str);
int			prints(char *str);

#endif
