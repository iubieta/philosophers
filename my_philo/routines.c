/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:55:53 by iubieta-          #+#    #+#             */
/*   Updated: 2024/09/18 21:15:44 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_philo *philo);
void	notify_status(t_philo *philo);


pthread_t	*start_routines(size_t *args, t_philo **philo, t_mutex_group *mutex_group)
{
	int i;
	pthread_t	*routines;

	i = 0;
	routines = malloc(sizeof(pthread_t) * args[0]);
	if (!routines)
		return (NULL);
	while (i < args[0])
	{
		pthread_create(routines[i], NULL, philo_routine, philo[i]);
		//SEGUIR AQUI
	}
	
}

void	philo_routine(t_philo *philo)
{
	philo->status = 1;
	notify_status(philo);
	while (status == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (pthread_mutex_lock(philo->right_fork))
			philo->status = 2;
		else
			pthread_mutex_unlock(philo->left_fork);
	}
	notify_status(philo);
	usleep(philo->t_eat);
	philo->status = 3;
	notify_status(philo);
	usleep(philo->t_sleep);
}

void	notify_status(t_philo *philo)
{
	struct timeval tv;
	char *status_str;
	
	pthread_mutex_lock(philo->write_lock);
	gettimeofday(&tv, NULL);
    printf("%ld",tv.tv_sec);
	if (philo->status == 1)
		status_str = "thinking";
	if (philo->status == 2)
		status_str = "eating";
	if (philo->status == 3)
		status_str = "sleeping";
	printf(" : Philo %lu is %s", philo->id, status_str);
}