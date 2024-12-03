/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iubieta- <iubieta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:01:35 by iubieta-          #+#    #+#             */
/*   Updated: 2024/12/03 16:08:49 by iubieta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo **table, t_mutex_group *mutex_group, size_t *args)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * args[1]);
	if (!philo)
		return (printe("ERROR initializing philosopher array\n"), 1);
	while (i < args[1])
	{
		fill_philo(&philo[i], i, args, mutex_group);
		printf("\nPhilo %lu : %p", philo[i].id, &philo[i]);
		print_philo_data(philo[i]);
		i++;
	}
	*table = philo;
	return (0);
}

void	fill_philo(t_philo *philo, size_t i, size_t *args,
	t_mutex_group *mutex_gr)
{
	philo->id = i;
	philo->status = 1;
	philo->death_flag = 0;
	philo->n_philos = args[1];
	philo->t_die = args[2];
	philo->t_eat = args[3];
	philo->t_sleep = args[4];
	philo->last_meal = millis();
	if (args[0] == 6)
		philo->n_meals = args[5];
	else
		philo->n_meals = 0;
	philo->left_fork = &mutex_gr->forks[i];
	if (i == args[1] - 1)
		philo->right_fork = &mutex_gr->forks[0];
	else
		philo->right_fork = &mutex_gr->forks[i + 1];
	philo->death_lock = &(mutex_gr->death_lock);
	philo->write_lock = &(mutex_gr->write_lock);
}

void	print_philo_data(t_philo philo)
{
	printf("\n\tStatus : %i", philo.status);
	printf("\n\tTime to die : %lu ms", philo.t_die);
	printf("\n\tTime to eat : %lu ms", philo.t_eat);
	printf("\n\tTime to sleep : %lu ms", philo.t_sleep);
	printf("\n\tNumber of meals : %lu", philo.n_meals);
	printf("\n\tLeft fork : %p", philo.left_fork);
	printf("\n\tRight fork : %p", philo.right_fork);
	printf("\n\tDeath lock : %p", philo.death_lock);
	printf("\n\tWrite lock : %p", philo.write_lock);
	printf("\n");
}

void	send_message(char *str, t_philo *philo)
{
	if (philo->death_flag == 1)
		return;
	lock_mutex(philo->write_lock);
	printf("%ld %lu %s\n", millis(), philo->id, str);
	unlock_mutex(philo->write_lock);
}
