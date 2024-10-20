/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:55:53 by iubieta-          #+#    #+#             */
/*   Updated: 2024/10/20 19:04:50 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg);
void	notify_status(t_philo *philo);
void	*monitor_routine(void *arg);
void	send_message(char *str, t_philo *philo);

pthread_t	*start_routines(size_t *args, t_philo **philo, t_mutex_group *mutex_group)
{
	int i;
	pthread_t	*routines;

	i = 0;
	routines = malloc(sizeof(pthread_t) * args[1]);
	if (!routines)
		return (NULL);
	while (i < args[1])
	{
		pthread_create(&routines[i], NULL, philo_routine, philo[i]);
		fflush(stdout);
		i++;
	}
	// printf("Crando hilo de monitorizacion\n");
	// pthread_create(&routines[i], NULL, monitor_routine, mutex_group);
	// printf("Hilo de monitorizacion creado\n");
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
}

void	*philo_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;

	send_message("Routine STARTED", philo);
	philo->status = 1;
	send_message("Thinking", philo);
	//notify_status(philo);
	while (philo->status == 1)
	{
		if (pthread_mutex_lock(philo->left_fork) == 0)
		{
			send_message("Took left fork", philo);
		}
		if (pthread_mutex_lock(philo->right_fork) == 0)
		{
			send_message("Took right fork", philo);
			philo->status = 2;
			//notify_status(philo);
			send_message("Eating", philo);
			usleep(philo->t_eat);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);			
			send_message("Left left fork", philo);
			send_message("Left right fork", philo);
		}
		else
		{
			send_message("Left left fork", philo);
			pthread_mutex_unlock(philo->left_fork);
			usleep(100);
		}
	}
	philo->status = 3;
	//notify_status(philo);
	send_message("Sleeping", philo);
	usleep(philo->t_sleep);
	send_message("Routine FINISHED", philo);
}

void	send_message(char *str, t_philo *philo)
{
	struct timeval tv;
	char *status_str;

	if (0 != pthread_mutex_lock(philo->write_lock))
	{
		printf("Error al bloquear el mutex");
		return;
	}
	printf("%p locked\n", philo->write_lock);
	gettimeofday(&tv, NULL);
    printf("\t%ld | %lu : %s\n",tv.tv_sec, philo->id, str);
	if(0!=pthread_mutex_unlock(philo->write_lock))
	{
		printf("Error al desbloquear el mutex\n");
	}
	printf("%p unlocked\n", philo->write_lock);
}

// void	notify_status(t_philo *philo)
// {
// 	struct timeval tv;
// 	char *status_str;

// 	status_str = "UNDEFINED";
// 	if (0 != pthread_mutex_lock(philo->write_lock))
// 	{
// 		printf("Error al bloquear el mutex");
// 	}
// 	if (philo->status == 1)
// 		status_str = "thinking";
// 	if (philo->status == 2)
// 		status_str = "eating";
// 	if (philo->status == 3)
// 		status_str = "sleeping";
// 	printf("ML\n");
// 	gettimeofday(&tv, NULL);
//     printf("\t%ld",tv.tv_sec);
// 	printf(": Philo %lu is %s\n", philo->id, status_str);
// 	fflush(stdout);
// 	if(0!=pthread_mutex_unlock(philo->write_lock))
// 	{
// 		printf("Error al desbloquear el mutex\n");
// 	}
// 	printf("MU\n");
// }
