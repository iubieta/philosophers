/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:56:50 by iubieta-          #+#    #+#             */
/*   Updated: 2024/11/02 20:06:02 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!dead_philo(philo) && !all_philos_finished(philo));
	return (NULL);
}

int	dead_philo(t_philo *philo)
{
	size_t	i;

	i = 0;
	while(i < philo->n_philos)
	{
		lock_mutex(philo[i].death_lock);
		if (philo[i].status != 4 && millis() - philo[i].last_meal > philo->t_die)
		{
			philo[i].status = 0;
			send_message("DIED", &philo[i]);
			return(1);
		}
		unlock_mutex(philo[i].death_lock);
		i++;
		usleep(100);
	}
	return (0);
}

int all_philos_finished(t_philo *philo)
{
	size_t i;
	size_t finished;

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