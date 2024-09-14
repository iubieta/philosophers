#include "philo.h"

pthread_mutex_t *init_forks(int n);

t_philo	**init_philos(t_philo **philo, int argc, char **argv)
{
	int i;
	int n;

	i = 0;
	n = ft_atoi(argv[1]);
	while (i < n)
	{
		philo[i] = malloc(sizeof(t_philo) * n);
		if (!philo[i])
			return(NULL);
		philo[i]->id = i;
		philo[i]->status = 0;
		philo[i]->t_die = ft_atoi(argv[2]);
		philo[i]->t_eat= ft_atoi(argv[3]);
		philo[i]->t_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			philo[i]->n_meals = ft_atoi(argv[5]);

		printf("\nPhilo %d : %p", philo[i]->id, &philo[i]);
		printf("\n\tStatus : %d", philo[i]->status);
		printf("\n\tTime to die : %d ms", philo[i]->t_die);
		printf("\n\tTime to eat : %d ms", philo[i]->t_eat);
		printf("\n\tTime to sleep : %d ms", philo[i]->t_sleep);
		printf("\n\tNumber of meals : %d", philo[i]->n_meals);
		printf("\n");

		i++;
	}
}

t_mutex_group	*init_mutex(t_mutex_group *mutex_group, char **argv)
{
	int n;

	if (pthread_mutex_init(&mutex_group->death_lock, NULL) != 0)
		return (printe("Fail to initiate 'death_lock'"), NULL);
	if (pthread_mutex_init(&mutex_group->write_lock, NULL) != 0)
		return (printe("Fail to initiate 'write_lock'"), NULL);
	n = ft_atoi(argv[1]);
	mutex_group->forks = init_forks(n);
	if (!mutex_group->forks)
		return (printe("Fail to initiate 'forks'"), NULL);
	return(mutex_group);
}

pthread_mutex_t *init_forks(int n)
{
	int	i;
	int j;
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
