/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta <iubieta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:56:50 by iubieta-          #+#    #+#             */
/*   Updated: 2024/11/16 19:19:49 by iubieta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!all_philos_finished(philo))
	{
		if (dead_philo(philo))
			force_philos_end(philo);
	}
	return (NULL);
}

int	dead_philo(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->n_philos && philo->death_flag == 0)
	{
		lock_mutex(philo[i].death_lock);
		if (philo[i].status != 4
			&& millis() - philo[i].last_meal > philo->t_die + 2)
		{
			philo[i].status = 0;
			send_message("DIED", &philo[i]);
			return (1);
		}
		unlock_mutex(philo[i].death_lock);
		i++;
		usleep(1000);
	}
	return (0);
}

int	all_philos_finished(t_philo *philo)
{
	size_t	i;
	size_t	finished;

	i = 0;
	finished = 0;
	while (i < philo->n_philos)
	{
		if (philo[i].status == 4)
			finished++;
		i++;
	}
	if (finished == philo->n_philos)
		return (1);
	return (0);
}

void force_philos_end(t_philo *philo)
{
	size_t i;
	
	i = 0;
	while (i < philo[0].n_philos)
	{
		philo[i].death_flag = 1;
		i++;
	}
	unlock_mutex(philo[0].death_lock);
}