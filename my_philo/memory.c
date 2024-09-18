/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:56:23 by iubieta-          #+#    #+#             */
/*   Updated: 2024/09/18 20:19:40 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t *init_forks(size_t n);

t_philo	**init_philos(t_philo **philo, t_mutex_group mutex_group, size_t *args)
{
	size_t i;
	size_t n;

	i = 0;
	n = args[1];
	while (i < n)
	{
		philo[i] = malloc(sizeof(t_philo) * n);
		if (!philo[i])
			return(NULL);
		philo[i]->id = i;
		philo[i]->status = 0;
		philo[i]->t_die = args[2];
		philo[i]->t_eat= args[3];
		philo[i]->t_sleep = args[4];
		if (args[0] == 6)
			philo[i]->n_meals = args[5];
		philo[i]->left_fork = &mutex_group.forks[i];
		if (i == n-1)
			philo[i]->right_fork = &mutex_group.forks[0];
		else
			philo[i]->right_fork = &mutex_group.forks[i+1];
		philo[i]->death_lock = &mutex_group.death_lock;
		philo[i]->write_lock = &mutex_group.write_lock;
		
		printf("\nPhilo %lu : %p", philo[i]->id, &philo[i]);
		printf("\n\tStatus : %i", philo[i]->status);
		printf("\n\tTime to die : %lu ms", philo[i]->t_die);
		printf("\n\tTime to eat : %lu ms", philo[i]->t_eat);
		printf("\n\tTime to sleep : %lu ms", philo[i]->t_sleep);
		printf("\n\tNumber of meals : %lu", philo[i]->n_meals);
		printf("\n\tLeft fork : %p", philo[i]->left_fork);
		printf("\n\tRight fork : %p", philo[i]->right_fork);
		printf("\n\tDeath lock : %p", philo[i]->death_lock);
		printf("\n\tWrite lock : %p", philo[i]->write_lock);
		printf("\n");

		i++;
	}
	return (philo);
}

t_mutex_group	*init_mutex(t_mutex_group *mutex_group, size_t *args)
{
	size_t n;

	if (pthread_mutex_init(&mutex_group->death_lock, NULL) != 0)
		return (printe("Fail to initiate 'death_lock'"), NULL);
	if (pthread_mutex_init(&mutex_group->write_lock, NULL) != 0)
		return (printe("Fail to initiate 'write_lock'"), NULL);
	n = args[1];
	mutex_group->forks = init_forks(n);
	if (!mutex_group->forks)
		return (printe("Fail to initiate 'forks'"), NULL);
	return(mutex_group);
}

pthread_mutex_t *init_forks(size_t n)
{
	size_t	i;
	size_t	j;
	pthread_mutex_t *forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!forks)
		return (free(forks), forks = NULL, NULL);
	while (i < n)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
		{
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&(forks[j++]));
			return (free(forks), forks = NULL, NULL);
		}
		i++;
	}
	return(forks);
}
