/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:23 by iubieta-          #+#    #+#             */
/*   Updated: 2024/10/31 17:28:16 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(pthread_mutex_t *mutex);
int	init_forks(pthread_mutex_t **forks, size_t n);

int	init_all_mutex(t_mutex_group *mutex_group, size_t *args)
{
	size_t n;

	n = args[1];
	if (0 != init_mutex(&(mutex_group->death_lock)))
		return (1);
	printf("Death lock : %p\n", &(mutex_group->death_lock));
	if (0 != init_mutex(&(mutex_group->write_lock)))
		return (2);
	printf("Write lock: %p\n", &(mutex_group->write_lock));
	if (0 != init_forks(&(mutex_group->forks), n))
		return (3);
	return (0);
}

int	init_mutex(pthread_mutex_t *mutex)
{
	if (0 != pthread_mutex_init(mutex, NULL))  // Inicializar el mutex
	{
		printe("ERROR initializing MUTEX\n");
		return (-1);
	}
	return (0);
}

int	init_forks(pthread_mutex_t **forks, size_t n)
{
	size_t	i;
	pthread_mutex_t *mutex_array;
	
	i = 0;
	mutex_array  = malloc(sizeof(pthread_mutex_t) * n);
	if (!mutex_array)
		return (printe("ERROR initializing forks mutex array\n"), 1);
	while (i < n)
	{
		if (0 != init_mutex(&(mutex_array[i])))
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&(mutex_array[i]));
			}
			free(mutex_array);
			mutex_array = NULL;
			return (2);
		}
		printf("Fork %lu : %p\n", i, &mutex_array[i]);
		i++;
	}
	*forks = mutex_array;
	return(0);
}

int init_philos(t_philo **table, t_mutex_group *mutex_group, size_t *args)
{
	size_t i;
	size_t n;
	t_philo *philo;
	
	i = 0;
	n = args[1];
	philo = malloc(sizeof(t_philo) * n);
	if (!philo)
		return (printe("ERROR initializing philosopher array\n"), 1);
	while (i < n)
	{
		philo[i].id = i;
		philo[i].status = 0;
		philo[i].t_die = args[2];
		philo[i].t_eat= args[3];
		philo[i].t_sleep = args[4];
		if (args[0] == 6)
			philo[i].n_meals = args[5];
		philo[i].left_fork = &mutex_group->forks[i];
		if (i == n-1)
			philo[i].right_fork = &mutex_group->forks[0];
		else
			philo[i].right_fork = &mutex_group->forks[i+1];
		philo[i].death_lock = &(mutex_group->death_lock);
		philo[i].write_lock = &(mutex_group->write_lock);

		printf("\nPhilo %lu : %p", philo[i].id, &philo[i]);
		printf("\n\tStatus : %i", philo[i].status);
		printf("\n\tTime to die : %lu ms", philo[i].t_die);
		printf("\n\tTime to eat : %lu ms", philo[i].t_eat);
		printf("\n\tTime to sleep : %lu ms", philo[i].t_sleep);
		printf("\n\tNumber of meals : %lu", philo[i].n_meals);
		printf("\n\tLeft fork : %p", philo[i].left_fork);
		printf("\n\tRight fork : %p", philo[i].right_fork);
		printf("\n\tDeath lock : %p", philo[i].death_lock);
		printf("\n\tWrite lock : %p", philo[i].write_lock);
		printf("\n");

		i++;
	}
	*table = philo;
	return (0);	
}
