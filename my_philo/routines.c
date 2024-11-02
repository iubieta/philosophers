/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:55:53 by iubieta-          #+#    #+#             */
/*   Updated: 2024/10/28 17:07:29by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


pthread_t	*start_routines(size_t *args, t_philo *philo)
{
	size_t i;
	pthread_t	*routines;

	i = 0;
	routines = malloc(sizeof(pthread_t) * args[1]);
	if (!routines)
		return (NULL);
	while (i < args[1])
	{
		if (&philo[i] != NULL)
			pthread_create(&routines[i], NULL, philo_routine, (void *)&philo[i]);
		i++;
	}
	return (routines);
}

void	*monitor_routine(void *arg)
{
	struct timeval tv;
	
	t_mutex_group	*mutex;
	mutex = (t_mutex_group *)arg;
	pthread_mutex_lock(&(mutex->write_lock));
	gettimeofday(&tv, NULL);
    printf("%ld\n",tv.tv_sec);
	fflush(stdout);
	pthread_mutex_unlock(&(mutex->write_lock));
	return(NULL);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;
	size_t i; 

	philo = (t_philo *)arg;
	i = 0;
	while (i < philo->n_meals && philo->status != 0)
	{
		philo->status = 1;
		send_message("Thinking", philo);
		eat(philo);
		philo->status = 3;
		send_message("Sleeping", philo);
		usleep(philo->t_sleep);
		i++;
	}
	send_message("Routine FINISHED", philo);
	return (NULL);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		lock_mutex(philo->left_fork);
		send_message("Took left fork", philo);
		lock_mutex(philo->right_fork);
		send_message("Took right fork", philo);
		philo->status = 2;
		update_last_meal(philo);
		send_message("Eating", philo);
		usleep(philo->t_eat);
	}
	else
	{
		lock_mutex(philo->right_fork);
		send_message("Took right fork", philo);
		lock_mutex(philo->left_fork);
		send_message("Took left fork", philo);
		philo->status = 2;
		update_last_meal(philo);
		send_message("Eating", philo);
		usleep(philo->t_eat);
	}
	unlock_mutex(philo->left_fork);
	unlock_mutex(philo->right_fork);
}

void	update_last_meal(t_philo *philo)
{
	struct timeval	tv;
	long			millis;

	lock_mutex(philo->death_lock);
	gettimeofday(&tv, NULL);
	millis = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo->last_meal = millis;
	unlock_mutex(philo->death_lock);
}