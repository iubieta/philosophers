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
	routines = malloc(sizeof(pthread_t) * (args[1] + 1));
	if (!routines)
		return (NULL);
	while (i < args[1])
	{
		if (&philo[i] != NULL)
			pthread_create(&routines[i], NULL, philo_routine, (void *)&philo[i]);
		i++;
	}
	pthread_create(&routines[i], NULL, monitor_routine, philo);
	return (routines);
}


void	*philo_routine(void *arg)
{
	t_philo *philo;
	size_t i; 

	philo = (t_philo *)arg;
	i = 0;
	philo->last_meal = millis();
	while (philo->n_meals == 0 || i < philo->n_meals)
	{
		philo->status = 1;
		send_message("Thinking", philo);
		eat(philo);
		philo->status = 3;
		send_message("Sleeping", philo);
		usleep(philo->t_sleep * 1000);
		i++;
	}
	send_message("Routine FINISHED", philo);
	philo->status = 4;
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
	}
	else
	{
		lock_mutex(philo->right_fork);
		send_message("Took right fork", philo);
		lock_mutex(philo->left_fork);
		send_message("Took left fork", philo);
	}
	lock_mutex(philo->death_lock);
	philo->status = 2;
	philo->last_meal = millis();
	send_message("Eating", philo);
	unlock_mutex(philo->death_lock);
	usleep(philo->t_eat * 1000);
	unlock_mutex(philo->left_fork);
	unlock_mutex(philo->right_fork);
}
