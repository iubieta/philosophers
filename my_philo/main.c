#include "philo.h"

t_mutex_group	*init_mutex(t_mutex_group *mutex_group, char **argv)
{
	int i;
	int n;
	
	pthread_mutex_init(&mutex_group->death_lock, NULL);
	pthread_mutex_init(&mutex_group->write_lock, NULL);
	i = 0;
	n = ft_atoi(argv[1]);
	mutex_group->forks = malloc(sizeof(pthread_mutex_t) * n);
	while (i < n)
		pthread_mutex_init(&(mutex_group->forks[i++]), NULL);
}

t_philo	**init_philos(t_philo **philo, int argc, char **argv)
{
	int i;
	int n;

	i = 0;
	n = ft_atoi(argv[1]);
	printf("\n--TABLE INFO--\n");
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
		i++;
	}
}

int main(int argc, char **argv)
{
	t_philo **table;

	printf("Number of philosophers: %d\n",ft_atoi(argv[1]));
	table = malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	init_philos(table, argc, argv);
}