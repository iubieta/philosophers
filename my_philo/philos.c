/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:01:35 by iubieta-          #+#    #+#             */
/*   Updated: 2024/11/02 14:24:19by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int init_philos(t_philo **table, t_mutex_group *mutex_group, size_t *args)
{
	size_t i;
	t_philo *philo;
	
	i = 0;
	philo = malloc(sizeof(t_philo) * args[1]);
	if (!philo)
		return (printe("ERROR initializing philosopher array\n"), 1);
	while (i < args[1])
	{
		fill_philo_data(&philo[i], i, args, mutex_group);
		printf("\nPhilo %lu : %p", philo[i].id, &philo[i]);
		print_philo_data(philo[i]);
		i++;
	}
	*table = philo;
	return (0);	
}

void	fill_philo_data(t_philo *philo, size_t i, size_t *args, t_mutex_group *mutex_group)
{
	philo->id = i;
	philo->status = 1;
	philo->t_die = args[2] * 1000;
	philo->t_eat= args[3] * 1000;
	philo->t_sleep = args[4] * 1000;
	if (args[0] == 6)
		philo->n_meals = args[5];
	philo->left_fork = &mutex_group->forks[i];
	if (i == args[1]-1)
		philo->right_fork = &mutex_group->forks[0];
	else
		philo->right_fork = &mutex_group->forks[i+1];
	philo->death_lock = &(mutex_group->death_lock);
	philo->write_lock = &(mutex_group->write_lock);
}

void	print_philo_data(t_philo philo)
{
	printf("\n\tStatus : %i", philo.status);
	printf("\n\tTime to die : %lu ms", philo.t_die/1000);
	printf("\n\tTime to eat : %lu ms", philo.t_eat/1000);
	printf("\n\tTime to sleep : %lu ms", philo.t_sleep/1000);
	printf("\n\tNumber of meals : %lu", philo.n_meals);
	printf("\n\tLeft fork : %p", philo.left_fork);
	printf("\n\tRight fork : %p", philo.right_fork);
	printf("\n\tDeath lock : %p", philo.death_lock);
	printf("\n\tWrite lock : %p", philo.write_lock);
	printf("\n");
}

void	send_message(char *str, t_philo *philo)
{
	struct timeval	tv;
	long			millis;

	gettimeofday(&tv, NULL);
	millis = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	lock_mutex(philo->write_lock);
    printf("  %ld  |  Philo %lu  :  %s\n", millis, philo->id, str);
	unlock_mutex(philo->write_lock);
}