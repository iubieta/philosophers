/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:23 by iubieta-          #+#    #+#             */
/*   Updated: 2024/11/02 14:13:27 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	init_mutex(pthread_mutex_t *mutex)
{
	if (0 != pthread_mutex_init(mutex, NULL))  // Inicializar el mutex
	{
		printe("ERROR initializing MUTEX\n");
		return (-1);
	}
	return (0);
}

void *lock_mutex(pthread_mutex_t *mutex)
{
    if (mutex == NULL)
	{
        printe("Mutex no inicializado\n");
		return (NULL);
    }
	if (0 != pthread_mutex_lock(mutex))
	{
		printf("Imposible bloquear el mutex %p\n", (void *)mutex);
		return (NULL);
	}
	return (mutex);
}

void *unlock_mutex(pthread_mutex_t *mutex)
{
    if (mutex == NULL)	
	{
        printe("Mutex no inicializado\n");
		return (NULL);
    }
	if (0 != pthread_mutex_unlock(mutex))
	{
		printf("Imposible desbloquear el mutex %p\n", (void *)mutex);
		return (NULL);
	}
	return (mutex);
}
