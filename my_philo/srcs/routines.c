/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:55:53 by iubieta-          #+#    #+#             */
/*   Updated: 2024/12/03 15:55:26 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	*start_routines(size_t *args, t_philo *philo)
{
	size_t		i;
	pthread_t	*routines;

	i = 0;
	routines = malloc(sizeof(pthread_t) * (args[1] + 1));
	if (!routines)
		return (NULL);
	while (i < args[1])
	{
		pthread_create(&routines[i], NULL, philo_routine, &philo[i]);
		i++;
	}
	pthread_create(&routines[i], NULL, monitor_routine, philo);
	return (routines);
}

void	*philo_routine(void *arg)
{
	size_t	i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	i = 0;
	philo->last_meal = millis();
	while (philo->death_flag == 0
		&& (philo->n_meals == 0 || i++ < philo->n_meals))
	{
		if (philo->death_flag != 1)
		{
			change_status(philo, 1);
			send_message("is thinking", philo);
		}
		eat(philo);
		if (philo->death_flag != 1)
		{
			change_status(philo, 3);
			send_message("is sleeping", philo);
			usleep(philo->t_sleep * 1000);
		}
	}
	//send_message("Routine FINISHED", philo);
	change_status(philo, 4);
	return (NULL);
}

int	eat(t_philo *philo)
{
	lock_mutex(philo->death_lock);
	if (philo->death_flag == 1 || one_philo_exception(philo) == 1)
		return (unlock_mutex(philo->death_lock), 0);
	unlock_mutex(philo->death_lock);
	if (philo->id % 2 == 0)
	{
		lock_mutex(philo->left_fork);
		send_message("Took left fork", philo);
		lock_mutex(philo->right_fork);
		send_message("Took right fork", philo);
	}
	else
	{
		lock_mutex(philo->right_fork);
		send_message("took right fork", philo);
		lock_mutex(philo->left_fork);
		send_message("took left fork", philo);
	}
	change_status(philo, 2);
	usleep(philo->t_eat * 1000);
	unlock_mutex(philo->left_fork);
	unlock_mutex(philo->right_fork);
	send_message("left left fork", philo);
	send_message("left right fork", philo);
	return (1);
}

int	one_philo_exception(t_philo *philo)
{
	if (philo->n_philos == 1)
	{
		lock_mutex(philo->left_fork);
		send_message("took left fork", philo);
		usleep(philo->t_die * 1000);
		unlock_mutex(philo->left_fork);
		send_message("died", philo);
		philo->death_flag = 1;
		return (1);
	}
	return (0);
}

void	change_status(t_philo *philo, int status)
{
	lock_mutex(philo->death_lock);
	philo->status = status;
	if (status == 2)
	{
		philo->last_meal = millis();
		send_message("is eating", philo);
	}
	unlock_mutex(philo->death_lock);
}
